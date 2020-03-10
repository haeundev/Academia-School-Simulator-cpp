#include "stdafx.h"
#include "TilePolyDraw.h"
#include "Tile.h"
#include "FollowMouseSprite.h"

void TilePolyDraw::Init()
{
	_vVertices.push_back(Vector2(0, 0));
	_vVertices.push_back(Vector2(0, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(_vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 0.4, 0.9, 0.4, 0.4 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(128);
	object->GetComponent<PolygonDraw>()->SetDepth((int)ZORDER::TILE_POLY_DRAW);
}

void TilePolyDraw::Update()
{
	object->GetComponent<PolygonDraw>()->SetVertices(_vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 0.4, 0.9, 0.4, 0.4 });

	Vector2 mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	Vector3 mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
	Vector3 mouseWorldPosition = Matrix3x3::Mul(mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
	float mouseX = mouseWorldPosition.x;
	float mouseY = (-1) * mouseWorldPosition.y;

	_currentIndex.x = (int)(mouseX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - mouseY) / GridHeight;

	// 부지 밖으로 나갔을 때나, 버튼을 클릭해야 할 때는 안 보이게
	if (_currentIndex.x < 0	|| _currentIndex.x > TotalGridX - 1 || _currentIndex.y < 0 || _currentIndex.y > TotalGridX - 1
		|| InputManager::GetInstance()->GetMousePosition().y < 40
		|| (InputManager::GetInstance()->GetMousePosition().x < 192 && InputManager::GetInstance()->GetMousePosition().y > 692)
		|| (InputManager::GetInstance()->GetMousePosition().x > 1390 && InputManager::GetInstance()->GetMousePosition().y > 790)
		|| (InputManager::GetInstance()->GetMousePosition().x < 430 && InputManager::GetInstance()->GetMousePosition().y < 80))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 0.9, 0.3, 0.2, 0.0 });
	}

	// 오브젝트의 크기에 따라서 PolyDraw의 크기 조정
	if (_followMouseSprite->GetSpriteFrameSize().x <= GridWidth * 1.5)
	{
		_vVertices[0].x = GRID_STARTPOINT.x + _currentIndex.x * GridWidth - GridWidth / 2;
		_vVertices[1].x = _vVertices[0].x + GridWidth;
	}
	else if (GridWidth * 1.5 < _followMouseSprite->GetSpriteFrameSize().x && _followMouseSprite->GetSpriteFrameSize().x <= GridWidth * 2)
	{
		_vVertices[0].x = GRID_STARTPOINT.x + _currentIndex.x * GridWidth - GridWidth / 2;
		_vVertices[1].x = _vVertices[0].x + GridWidth * 2;
	}
	else if (GridWidth * 2 < _followMouseSprite->GetSpriteFrameSize().x && _followMouseSprite->GetSpriteFrameSize().x <= GridWidth * 3)
	{
		_vVertices[0].x = GRID_STARTPOINT.x + _currentIndex.x * GridWidth - GridWidth / 2;
		_vVertices[1].x = _vVertices[0].x + GridWidth * 3;
	}

	if (_followMouseSprite->GetSpriteFrameSize().y <= GridHeight * 1.5)
	{
		_vVertices[0].y = GRID_STARTPOINT.y - _currentIndex.y * GridHeight;
		_vVertices[1].y = _vVertices[0].y;
		object->GetComponent<PolygonDraw>()->SetStrokeWidth(128);
	}
	else if (GridHeight * 1.5 < _followMouseSprite->GetSpriteFrameSize().y && _followMouseSprite->GetSpriteFrameSize().y <= GridHeight * 2)
	{
		_vVertices[0].y = GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight/2;
		_vVertices[1].y = _vVertices[0].y;
		object->GetComponent<PolygonDraw>()->SetStrokeWidth(256);
	}
	else if (GridHeight * 2 < _followMouseSprite->GetSpriteFrameSize().y && _followMouseSprite->GetSpriteFrameSize().y <= GridHeight * 3)
	{
		_vVertices[0].y = GRID_STARTPOINT.y - _currentIndex.y * GridHeight;
		_vVertices[1].y = _vVertices[0].y;
		object->GetComponent<PolygonDraw>()->SetStrokeWidth(128 * 3);
	}
}