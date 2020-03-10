#include "stdafx.h"
#include "TileCheck.h"
#include "TileMap.h"
#include "NewBuilding.h"
#include "BuildingComponent.h"

void TileCheck::Init()
{
	vTotal = map->GetComponent<TileMap>()->GetVTotal();

	vector<Vector2> pos;
	pos.push_back(Vector2(-TILEWIDTH / 2, TILEHEIGHT / 2));
	pos.push_back(Vector2(TILEWIDTH / 2, TILEHEIGHT / 2));
	pos.push_back(Vector2(TILEWIDTH / 2, -TILEHEIGHT / 2));
	pos.push_back(Vector2(-TILEHEIGHT / 2, -TILEHEIGHT / 2));

	newBuildingSprite = newBuilding->GetComponent<Sprite>();
	dimension.x = ceil(newBuildingSprite->GetFrameSize().x*1.5 / TILEWIDTH);
	dimension.y = ceil(newBuildingSprite->GetFrameSize().y*1.5 / TILEHEIGHT);

	for (int i = 0; i < dimension.x; i++)
	{
		for (int j = 0; j < dimension.y; j++)
		{
			Object* normalTile = Object::CreateObject(object);
			auto tilePoly = normalTile->AddComponent<PolygonDraw>();
			tilePoly->SetVertices(pos);
			vTemp.push_back(normalTile);
			normalTile->SetIsActive(false);
		}
	}

}

void TileCheck::Update()
{
	if (object->GetComponent<BoxCollider>()->GetOnMouse())
		DrawTile();
}

void TileCheck::OnMouseDown()
{
	if (((NewBuilding*)((newBuilding->GetComponent<BuildingComponent>()->GetBuilding())))->GetFixedPosition())
		return;

	if (!newBuilding->GetIsActive())
		return;

	//CHECK IF ALLOWED
	for (int i = 0; i < dimension.x; i++)
		for (int j = 0; j < dimension.y; j++)
		{
			if (vTotal[(GetMouseIndex().x - dimension.x / 2 + i) * TILENUM_Y + GetMouseIndex().y + dimension.y / 2 - j]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::NONE)
				return;

			//vTotal[(GetMouseIndex().x - dimension.x / 2 + i) * TILENUM_Y + GetMouseIndex().y + dimension.y / 2 - j]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::NONE);

		}
			

	//FIX POSITION 
	for (int i = 0; i < dimension.x; i++)
		for (int j = 0; j < dimension.y; j++)
			vTotal[(GetMouseIndex().x - dimension.x / 2 + i) * TILENUM_Y + GetMouseIndex().y + dimension.y / 2 - j]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::WALL);
		

	((NewBuilding*)((newBuilding->GetComponent<BuildingComponent>()->GetBuilding())))->SetFixedPosition(true);
	newBuilding->GetComponent<Sprite>()->SetOpacity(1.f);
	object->SetIsActive(false);
	map->GetComponent<TileMap>()->SetTileView(false);
}

void TileCheck::DrawTile()
{
	if (!newBuilding->GetIsActive())
		return;

	//마우스 좌표  
	auto mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	Vector3 mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
	Vector3 mouseWorldPosition = Matrix3x3::Mul(mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());

	//float mouseX = InputManager::GetInstance()->GetMouseWorldPosition().x - CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetPosition().x;
	//float mouseY = -CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetPosition().y - InputManager::GetInstance()->GetMouseWorldPosition().y;

	float mouseX = mouseWorldPosition.x;
	float mouseY = (-1)*mouseWorldPosition.y;


	index_X = (int)(mouseX - (vTotal[0]->GetTransform()->GetPosition().x - TILEWIDTH / 2)) / TILEWIDTH;
	index_Y = (int)(vTotal[0]->GetTransform()->GetPosition().y + TILEHEIGHT / 2 - mouseY) / TILEHEIGHT;

	//예외 처리 
	if (index_Y + index_X * TILENUM_Y < 0 || index_Y + index_X * TILENUM_Y > vTotal.size() - 1)
		return;
	if (mouseY > vTotal[TILENUM_Y]->GetTransform()->GetPosition().y + TILEHEIGHT / 2)
		return;
	if (index_X - dimension.x / 2 <= 0 || index_X + dimension.x / 2 >= TILENUM_X - 1)
		return;
	/*if (index_Y + dimension.y / 2 <= 0 || index_Y - dimension.y / 2 >= TILENUM_Y - 1)
		return;*/


	//타일 그려주기 
	for (int i = 0; i < dimension.x; i++)
	{
		for (int j = 0; j < dimension.y; j++)
		{
			auto tilePoly = vTemp[i * dimension.y + j]->GetComponent<PolygonDraw>();

			vTemp[i * dimension.y + j]->SetIsActive(true);
			tilePoly->GetTransform()->SetPosition(vTotal[(index_X - dimension.x / 2 + i) * TILENUM_Y + index_Y + dimension.y / 2 - 1 - j]->GetTransform()->GetPosition());
			tilePoly->SetDepth(4);


			if (vTotal[(index_X - dimension.x / 2 + i) * TILENUM_Y + index_Y + dimension.y / 2  - j]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::NONE)
				tilePoly->SetColor(Color{ 1,0,0,1 });
			else
				tilePoly->SetColor(Color{ 0,1,0,1 });
		}
	}

	SetMouseIndex(Vector2(index_X, index_Y));
}

