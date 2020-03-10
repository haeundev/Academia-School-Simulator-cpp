#include "stdafx.h"
#include "DeleteObjects.h"
#include "Tile.h"
#include "ObjectIndex.h"

void DeleteObjects::Init()
{
	_sprite = object->GetComponent<Sprite>();
}

void DeleteObjects::Update()
{
	if (object->GetTag() == "Floor") return;

	_mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	_mousePosition_V3 = Vector3(_mousePosition.x, _mousePosition.y, 1);
	_mouseWorldPosition = Matrix3x3::Mul(_mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
	_mouseX = _mouseWorldPosition.x;
	_mouseY = (-1) * _mouseWorldPosition.y;

	_currentIndex.x = (int)(_mouseX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - _mouseY) / GridHeight;

	if (InputManager::GetInstance()->GetKey(VK_RBUTTON) && object->GetComponent<Collider>()->GetOnMouse())
	{
		if (!object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition())) return;

		object->SetIsActive(false);

		if (2 * GridWidth < _sprite->GetFrameSize().x && _sprite->GetFrameSize().x <= 3 * GridWidth)
		{
			// 3 x 1
			if (_sprite->GetFrameSize().y <= 1.5 * GridHeight)
			{
				_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

				// 加己 函版
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 2]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
			}
			// 3 x 2
			if (1.5 * GridHeight < _sprite->GetFrameSize().y && _sprite->GetFrameSize().y <= 2 * GridHeight)
			{
				_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));

				// 加己 函版
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 2]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 2]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
			}
		}
		else if (GridWidth < _sprite->GetFrameSize().x && _sprite->GetFrameSize().x <= 2 * GridWidth)
		{
			// 2 x 1
			if (_sprite->GetFrameSize().y <= 1.5 * GridHeight)
			{
				_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

				// 加己 函版
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
			}
			// 2 x 2
			if (1.5 * GridHeight < _sprite->GetFrameSize().y && _sprite->GetFrameSize().y <= 2 * GridHeight)
			{
				_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));

				// 加己 函版
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
			}
			// 2 x 3
			if (2 * GridHeight < _sprite->GetFrameSize().y && _sprite->GetFrameSize().y <= 3 * GridHeight)
			{
				_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

				// 加己 函版
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX * 2]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX * 2 + 1]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
			}
		}
		else
		{
			// 1 x 1
			if (_sprite->GetFrameSize().y <= 1.5 * GridHeight)
			{
				_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

				if ((*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_WALL)
				{
					(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) - 1]->GetComponent<Tile>()->FlagRightOff();
					(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) - TotalGridX]->GetComponent<Tile>()->FlagBottomOff();
					(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + 1]->GetComponent<Tile>()->FlagLeftOff();
					(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->FlagTopOff();
				}

				// 加己 函版
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);

				if (object->GetTag() == "Wall")
				{
					(*_vTiles)[object->GetComponent<ObjectIndex>()->GetIndex().x + (object->GetComponent<ObjectIndex>()->GetIndex().y * TotalGridX) + 1]->GetComponent<Tile>()->FlagLeftOff();
					(*_vTiles)[object->GetComponent<ObjectIndex>()->GetIndex().x + (object->GetComponent<ObjectIndex>()->GetIndex().y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->FlagTopOff();
					(*_vTiles)[object->GetComponent<ObjectIndex>()->GetIndex().x + (object->GetComponent<ObjectIndex>()->GetIndex().y * TotalGridX) - 1]->GetComponent<Tile>()->FlagRightOff();
					(*_vTiles)[object->GetComponent<ObjectIndex>()->GetIndex().x + (object->GetComponent<ObjectIndex>()->GetIndex().y * TotalGridX) - TotalGridX]->GetComponent<Tile>()->FlagBottomOff();

					for (auto w : _vWalls)
					{
						w->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Build/Walls/" + w->GetName() +
							to_string((int)(*_vTiles)[
								w->GetComponent<ObjectIndex>()->GetIndex().x + (w->GetComponent<ObjectIndex>()->GetIndex().y * TotalGridX)]
								->GetComponent<Tile>()->GetFlag()) + ".png"));
					}
				}
			}
			// 1 x 2
			if (1.5 * GridHeight < _sprite->GetFrameSize().y && _sprite->GetFrameSize().y <= 2 * GridHeight)
			{
				_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth,
					GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));

				// 加己 函版
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX)]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
				(*_vTiles)[_currentIndex.x + (_currentIndex.y * TotalGridX) + TotalGridX]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
			}
		}
	}
}