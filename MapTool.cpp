#include "stdafx.h"
#include "MapTool.h"
#include "FollowMouseSprite.h"
#include "Tile.h"
#include "DeleteObjects.h"
#include "ObjectData.h"
#include "ObjectIndex.h"
#include "RealtimePoly.h"
#include "CharacterManager.h"
#include "WorkerMove.h"
#include "Budget.h"
#include <fstream>
#pragma warning (disable:4996)

void MapTool::Init()
{
	_realtimePoly = Object::CreateObject();
	_realtimePoly->AddComponent<RealtimePoly>();
	_realtimePoly->GetComponent<RealtimePoly>()->SetVTilesLink(_vTiles);

	this->AddObserver(SceneManager::GetInstance()->GetNowScene()->GetChildByName("CharacterManager")->GetComponent<CharacterManager>());

	for (int i = 1; i <= 10; i++)
	{
		tagWork a;
		a.isDone = false;
		a.isDummy = true;
		a.object = Object::CreateObject();
		a.object->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("ImagesForPlacing/transparentTile.png"));
		a.workAreaIndex = Vector2(i, 0);

		queue<tagWork> b;
		b.push(a);

		_mWorkLoad.insert(pair(to_string(i), b));
	}
}

void MapTool::Update()
{
	_mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	_mousePosition_V3 = Vector3(_mousePosition.x, _mousePosition.y, 1);
	_mouseWorldPosition = Matrix3x3::Mul(_mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
	_mouseX = _mouseWorldPosition.x;
	_mouseY = (-1) * _mouseWorldPosition.y;

	_currentIndex.x = (int)(_mouseX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - _mouseY) / GridHeight;

	PlaceObjects();
	PlaceFloors();
	PlaceWalls();

	if (_followMouseSprite->GetSStoreImgKey().size())
		_attribute = _attributeInfo->GetMAttributeData()[_followMouseSprite->GetSStoreImgKey().top()].attribute;

	if (InputManager::GetInstance()->GetKey(VK_CONTROL) && InputManager::GetInstance()->GetKeyDown('I'))
		Save();

	if (InputManager::GetInstance()->GetKey(VK_CONTROL) && InputManager::GetInstance()->GetKeyDown('O'))
		Load();

	// 바닥을 배치할 때만 대각선 폴리 보여줌
	if (InputManager::GetInstance()->GetKey(VK_SHIFT) && InputManager::GetInstance()->GetKey(VK_LBUTTON) && _attribute == ATTRIBUTE::TILE_FLOOR)
		_realtimePoly->SetIsActive(true);
	else
		_realtimePoly->SetIsActive(false);
}

void MapTool::PlaceObjects()
{
	// 여기서는 벽, 바닥 배치하지 않음.
	if (_attribute == ATTRIBUTE::TILE_WALL 
		|| _attribute == ATTRIBUTE::TILE_FLOOR) return;

	// 부지 밖으로 나가면 배치가 불가능.
	if (_currentIndex.x < 0 || _currentIndex.x > TotalGridX - 1 || _currentIndex.y < 0 || _currentIndex.y > TotalGridX - 1) return;

	if (InputManager::GetInstance()->GetKey(VK_SHIFT)
		&& InputManager::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		// 들고 있는 이미지가 없으면 return
		if (!_followMouseSprite->GetSStoreImgKey().size())
			return;

		// 이미 막혀있는 속성일 경우 return
		if ((*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_WALL
			|| (*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_OBJECT_BLOCKED
			|| (*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_OBJECT_OPEN)
			return;

		//■■■■■■■■■■■■■■ 이미지를 배치하는 부분 ■■■■■■■■■■■■■■

		// 새 이미지 생성
		Object* newObj = Object::CreateObject();
		newObj->SetName(_followMouseSprite->GetSStoreImgKey().top());
		newObj->AddComponent<BoxCollider>();
		newObj->AddComponent<DeleteObjects>();
		newObj->GetComponent<DeleteObjects>()->SetVTilesLink(_vTiles);

		auto newObjSprite = newObj->AddComponent<Sprite>();
		newObjSprite->SetSprite(ImageManager::GetInstance()->AddImage("ImagesForPlacing/" + _followMouseSprite->GetSStoreImgKey().top() + ".png"));
		newObjSprite->SetDepth((int)ZORDER::OBJECT);
		newObjSprite->SetOpacity(0.3);

		// 예산 차감
		_cost = _attributeInfo->GetMAttributeData()[newObj->GetName()].cost;
		_budget->BudgetMinus(_cost);
		Notify(MTYPE::BUDGET_MINUS, to_string(_cost));

		// Save & Load를 위해 저장
		_vAllItems.push_back(newObj);

		tagWork a;
		a.object = newObj;
		a.workAreaIndex = _currentIndex;
		a.isDummy = false;
		a.isDone = false;

		if (i > 10) i = 1;

		_mWorkLoad[to_string(i)].push(a);

		i++;

		Notify(MTYPE::WORK, "Added");

		//if (object->GetName() == "StudentChair" ||)

		if (2 * GridWidth < newObjSprite->GetFrameSize().x && newObjSprite->GetFrameSize().x <= 3 * GridWidth)
		{
			// 3 x 1
			if (newObjSprite->GetFrameSize().y <= 1.5 * GridHeight)
			{
				newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

				// 속성 변경
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 2]->GetComponent<Tile>()->SetAttribute(_attribute);
			}
			// 3 x 2
			if (1.5 * GridHeight < newObjSprite->GetFrameSize().y && newObjSprite->GetFrameSize().y <= 2 * GridHeight)
			{
				newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));

				// 속성 변경
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 2]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 2]->GetComponent<Tile>()->SetAttribute(_attribute);
			}
		}
		else if (GridWidth < newObjSprite->GetFrameSize().x && newObjSprite->GetFrameSize().x <= 2 * GridWidth)
		{
			// 2 x 1
			if (newObjSprite->GetFrameSize().y <= 1.5 * GridHeight)
			{
				newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

				// 속성 변경
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
			}
			// 2 x 2
			if (1.5 * GridHeight < newObjSprite->GetFrameSize().y && newObjSprite->GetFrameSize().y <= 2 * GridHeight)
			{
				newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));

				// 속성 변경
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
			}
			// 2 x 3
			if (2 * GridHeight < newObjSprite->GetFrameSize().y && newObjSprite->GetFrameSize().y <= 3 * GridHeight)
			{
				newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

				// 속성 변경
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX * 2]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX * 2 + 1]->GetComponent<Tile>()->SetAttribute(_attribute);
			}
		}
		else
		{
			// 1 x 1
			if (newObjSprite->GetFrameSize().y <= 1.5 * GridHeight)
			{
				newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));
				
				// 속성 변경
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
			}
			// 1 x 2
			if (1.5 * GridHeight < newObjSprite->GetFrameSize().y && newObjSprite->GetFrameSize().y <= 2 * GridHeight)
			{
				newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));
				
				// 속성 변경
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(_attribute);
			}
		}
	}
}

void MapTool::PlaceWalls()
{
	// 지금 배치하는 게 벽이 아니면 return
	if (_attribute != ATTRIBUTE::TILE_WALL) return;

	// 부지 밖으로 나가면 배치가 불가능.
	if (_currentIndex.x < 1 || _currentIndex.x > 48 || _currentIndex.y < 1 || _currentIndex.y > 48) return;

	// 들고 있는 이미지가 없으면 return.
	if (!_followMouseSprite->GetSStoreImgKey().size()) return;

	// 이미 막혀있는 속성일 경우 return
	if ((*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_OBJECT_BLOCKED
		|| (*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_WALL)
		return;

	if (InputManager::GetInstance()->GetKey(VK_SHIFT)
		&& InputManager::GetInstance()->GetKey(VK_LBUTTON))
	{
		// 새 이미지 생성
		_newWall = Object::CreateObject();
		_newWall->SetTag("Wall");
		_newWall->SetName(_followMouseSprite->GetSStoreImgKey().top());
		_newWallSprite = _newWall->AddComponent<Sprite>();
		_newWallSprite->SetSprite(ImageManager::GetInstance()->AddImage("ImagesForPlacing/" + _followMouseSprite->GetSStoreImgKey().top() + ".png"));
		_newWallSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth,
			GRID_STARTPOINT.y - _currentIndex.y * GridHeight));
		_newWallSprite->SetDepth((int)ZORDER::WALL);
		_newWall->AddComponent<BoxCollider>();
		_newWall->AddComponent<DeleteObjects>();
		_newWall->GetComponent<DeleteObjects>()->SetVTilesLink(_vTiles);
		_newWall->GetComponent<DeleteObjects>()->SetVWallsLink(_vWalls);
		_newWall->AddComponent<ObjectIndex>();
		_newWall->GetComponent<ObjectIndex>()->SetIndex(_currentIndex);

		_vWalls.push_back(_newWall);

		// 예산 차감
		_cost = _attributeInfo->GetMAttributeData()[_newWall->GetName()].cost;
		_budget->BudgetMinus(_cost);
		Notify(MTYPE::BUDGET_MINUS, to_string(_cost));

		// 속성 변경
		(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_WALL);

		// flag 변경
		(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->FlagLeftOn();
		(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->FlagTopOn();
		(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) - 1]->GetComponent<Tile>()->FlagRightOn();
		(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) - TotalGridX]->GetComponent<Tile>()->FlagBottomOn();
		
		_newWallSprite->SetSprite(ImageManager::GetInstance()->AddImage("Build/Walls/" + _followMouseSprite->GetSStoreImgKey().top() + 
			to_string((int)(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetFlag()) + ".png"));

		for (auto w : _vWalls)
		{
			w->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Build/Walls/" + w->GetName() +
				to_string((int)(*_vTiles)[
					w->GetComponent<ObjectIndex>()->GetIndex().x + (w->GetComponent<ObjectIndex>()->GetIndex().y * TotalGridX)]
					->GetComponent<Tile>()->GetFlag()) + ".png"));
		}
	}
}

void MapTool::PlaceFloors()
{
	// 지금 배치하는 게 바닥이 아니면 return
	if (_attribute != ATTRIBUTE::TILE_FLOOR) return;

	// 부지 밖으로 나가면 배치가 불가능.
	if (_currentIndex.x < 0 || _currentIndex.x > TotalGridX - 1 || _currentIndex.y < 0 || _currentIndex.y > TotalGridX - 1) return;

	// 들고 있는 이미지가 없으면 return
	if (!_followMouseSprite->GetSStoreImgKey().size())
		return;

	// 이미 막혀있는 속성일 경우 return
	if ((*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_WALL)
		return;

	if (!InputManager::GetInstance()->GetKey(VK_SHIFT)) return;

	if (InputManager::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		_floorStartIndex = _currentIndex;
	}
	if (InputManager::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
		_floorEndIndex = _currentIndex;

		vector<Vector2> vPositions;

		for (auto t : (*_vTiles))
		{
			if (t->GetComponent<Tile>()->GetIndex().x >= _floorStartIndex.x
				&& t->GetComponent<Tile>()->GetIndex().x <= _floorEndIndex.x
				&& t->GetComponent<Tile>()->GetIndex().y >= _floorStartIndex.y
				&& t->GetComponent<Tile>()->GetIndex().y <= _floorEndIndex.y
				)
			{
				vPositions.push_back(t->GetComponent<Tile>()->GetIndex());
			}
		}

		for (auto p : vPositions)
		{
			// 새 이미지 생성
			Object* newObj = Object::CreateObject();
			newObj->AddComponent<BoxCollider>();
			//newObj->AddComponent<DeleteObjects>();
			//newObj->GetComponent<DeleteObjects>()->SetVTilesLink(&(*_vTiles));
			auto newObjSprite = newObj->AddComponent<Sprite>();
			newObjSprite->SetSprite(ImageManager::GetInstance()->AddImage("ImagesForPlacing/" + _followMouseSprite->GetSStoreImgKey().top() + ".png"));
			newObj->SetTag("Floor");
			newObj->SetName(_followMouseSprite->GetSStoreImgKey().top());
			newObjSprite->SetDepth((int)ZORDER::FLOOR);

			// 예산 차감
			_cost = _attributeInfo->GetMAttributeData()[newObj->GetName()].cost;
			_budget->BudgetMinus(_cost);
			Notify(MTYPE::BUDGET_MINUS, to_string(_cost));

			// Save & Load를 위해 저장
			_vAllItems.push_back(newObj);

			// 1 x 1
			newObjSprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + p.x * GridWidth, GRID_STARTPOINT.y - p.y * GridHeight));

			// 속성 변경
			(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(_attribute);
		}
	}
}

void MapTool::Save()
{
	vector<ObjData> data;
	ofstream streamData;
	for (auto i : _vAllItems)
	{
		ObjData tempData;
		Sprite* nowSprite = i->GetComponent<Sprite>();
		strcpy(tempData.name, nowSprite->GetSprite()->GetPath().c_str());
		tempData.position = i->GetTransform()->GetPosition();
		tempData.depth = nowSprite->GetDepth();
		tempData.isActive = i->GetIsActive();
		data.push_back(tempData);
	}
	streamData.open("Resources/Data/ObjectData.map", ios::binary);
	int size = _vAllItems.size();
	streamData.write((const char*)&size, sizeof(int));
	for (auto d : data)
		streamData.write((const char*)&d, sizeof(ObjData));

	streamData.close();


	vector<TileData> tileData;
	ofstream streamTile;
	for (auto i : (*_vTiles))
	{
		TileData tempData;
		tempData.position = i->GetTransform()->GetPosition();
		tempData.attribute = i->GetComponent<Tile>()->GetAttribute();
		tempData.flag = i->GetComponent<Tile>()->GetFlag();
		tempData.index = i->GetComponent<Tile>()->GetIndex();
		tempData.isActive = i->GetIsActive();
		tileData.push_back(tempData);
	}
	streamTile.open("Resources/Data/TileData.map", ios::binary);
	int size2 = (*_vTiles).size();
	streamTile.write((const char*)&size2, sizeof(int));
	for (auto d : tileData)
		streamTile.write((const char*)&d, sizeof(TileData));

	// 타일 속성 쓰기
	streamTile.write((const char*)&Vector2((GridWidth*TotalGridX), (GridHeight*TotalGridY)), sizeof(Vector2));
	streamTile.close();


	vector<WallData> wallData;
	ofstream streamWalls;
	for (auto i : _vWalls)
	{
		WallData tempData;
		Sprite* nowSprite = i->GetComponent<Sprite>();
		tempData.index = i->GetComponent<ObjectIndex>()->GetIndex();
		tempData.position = i->GetTransform()->GetPosition();
		strcpy(tempData.name, i->GetName().c_str());
		strcpy(tempData.tag, i->GetTag().c_str());
		tempData.depth = nowSprite->GetDepth();
		tempData.isActive = i->GetIsActive();
		wallData.push_back(tempData);
	}
	streamWalls.open("Resources/Data/WallData.map", ios::binary);
	int size3 = _vWalls.size();
	streamWalls.write((const char*)&size3, sizeof(int));
	for (auto d : wallData)
		streamWalls.write((const char*)&d, sizeof(WallData));

	streamWalls.write((const char*)&Vector2((GridWidth * TotalGridX), (GridHeight * TotalGridY)), sizeof(Vector2));
	streamWalls.close();
}

void MapTool::Load()
{
	vector<ObjData> ObData;
	ifstream streamData;
	streamData.open("Resources/Data/ObjectData.map", ios::binary);
	int size = 0;
	streamData.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++)
	{
		ObjData newData;
		streamData.read((char*)&newData, sizeof(ObjData));
		ObData.push_back(newData);
	}
	streamData.read((char*)&Vector2((GridWidth * TotalGridX), (GridHeight * TotalGridY)), sizeof(Vector2));
	streamData.close();

	for (auto i : _vAllItems)
		i->SetIsActive(false);
	_vAllItems.clear();

	// 읽어온 데이터로 새로 만든다.
	for (auto d : ObData)
	{
		Object* newObject = Object::CreateObject();
		newObject->AddComponent<BoxCollider>();
		newObject->AddComponent<DeleteObjects>();
		newObject->GetComponent<DeleteObjects>()->SetVTilesLink(&(*_vTiles));
		auto sprite = newObject->AddComponent<Sprite>();
		sprite->SetSprite(ImageManager::GetInstance()->AddImage(d.name));
		sprite->SetDepth(d.depth);
		newObject->GetTransform()->SetPosition(d.position);
		newObject->SetIsActive(d.isActive);
		_vAllItems.push_back(newObject);
	}


	vector<TileData> tileData;
	ifstream streamTile;
	streamTile.open("Resources/Data/TileData.map", ios::binary);
	int size2 = 0;
	streamTile.read((char*)&size2, sizeof(int));
	for (int i = 0; i < size2; i++)
	{
		TileData newData;
		streamTile.read((char*)&newData, sizeof(TileData));
		tileData.push_back(newData);
	}
	streamTile.read((char*)&Vector2((GridWidth * TotalGridX), (GridHeight * TotalGridY)), sizeof(Vector2));
	streamTile.close();

	for (auto i : (*_vTiles))
		i->SetIsActive(false);
	(*_vTiles).clear();

	// 읽어온 데이터로 새로 만든다.
	for (auto d : tileData)
	{
		Object* newTile = Object::CreateObject();
		newTile->AddComponent<Tile>();
		newTile->GetComponent<Tile>()->SetAttribute(d.attribute);
		newTile->GetComponent<Tile>()->SetFlag(d.flag);
		newTile->SetIsActive(d.isActive);
		newTile->GetTransform()->SetPosition(d.position);

		(*_vTiles).push_back(newTile);
	}


	vector<WallData> wallData;
	ifstream streamWalls;
	streamWalls.open("Resources/Data/WallData.map", ios::binary);
	int size3 = 0;
	streamWalls.read((char*)&size3, sizeof(int));
	for (int i = 0; i < size3; i++)
	{
		WallData newData;
		streamWalls.read((char*)&newData, sizeof(WallData));
		wallData.push_back(newData);
	}
	streamWalls.read((char*)&Vector2((GridWidth * TotalGridX), (GridHeight * TotalGridY)), sizeof(Vector2));
	streamWalls.close();

	for (auto i : _vWalls)
		i->SetIsActive(false);
	_vWalls.clear();

	// 읽어온 데이터로 새로 만든다.
	for (auto d : wallData)
	{
		Object* newWall = Object::CreateObject();
		newWall->GetTransform()->SetPosition(d.position);

		newWall->AddComponent<BoxCollider>();
		newWall->AddComponent<DeleteObjects>();
		newWall->GetComponent<DeleteObjects>()->SetVTilesLink(&(*_vTiles));
		newWall->AddComponent<ObjectIndex>();
		newWall->GetComponent<ObjectIndex>()->SetIndex(d.index);
		newWall->SetName(d.name);
		newWall->SetTag(d.tag);
		newWall->SetIsActive(d.isActive);
		auto sprite = newWall->AddComponent<Sprite>();
		sprite->SetDepth(d.depth);

		string str(d.name);

		sprite->SetSprite(ImageManager::GetInstance()->AddImage("Build/Walls/" + str +
			to_string((int)(*_vTiles)[d.index.x + (d.index.y * TotalGridX)]->GetComponent<Tile>()->GetFlag()) + ".png"));

		_vWalls.push_back(newWall);
	}

	for (int i = 0; i < _vWalls.size(); i++)
	{
		(*_vTiles)[_vWalls[i]->GetComponent<ObjectIndex>()->GetIndex().x + TotalGridX * _vWalls[i]->GetComponent<ObjectIndex>()->GetIndex().y]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_WALL);
	}

	for (auto w : _vWalls)
	{
		w->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Build/Walls/" + w->GetName() +
			to_string((int)(*_vTiles)[
				w->GetComponent<ObjectIndex>()->GetIndex().x + (w->GetComponent<ObjectIndex>()->GetIndex().y * TotalGridX)]
				->GetComponent<Tile>()->GetFlag()) + ".png"));
	}
}