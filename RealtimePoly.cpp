#include "stdafx.h"
#include "RealtimePoly.h"

void RealtimePoly::Init()
{
	_vVertices.push_back(Vector2(0, 0));
	_vVertices.push_back(Vector2(0, 0));

	_poly = object->AddComponent<PolygonDraw>();
	_poly->SetColor({ 0.2, 0.6, 0.6, 0.3 });
	_poly->SetDepth((int)ZORDER::ZONE);

	_poly->SetVertices(_vVertices);
}

void RealtimePoly::Update()
{
	// 부지 밖으로 나갔을 때나, 버튼을 클릭해야 할 때는 안 보이게
	if (_currentIndex.x < 0 || _currentIndex.x > TotalGridX - 1 || _currentIndex.y < 0 || _currentIndex.y > TotalGridX - 1
		|| InputManager::GetInstance()->GetMousePosition().y < 40
		|| (InputManager::GetInstance()->GetMousePosition().x < 192 && InputManager::GetInstance()->GetMousePosition().y > 692)
		|| (InputManager::GetInstance()->GetMousePosition().x > 1390 && InputManager::GetInstance()->GetMousePosition().y > 790)
		|| (InputManager::GetInstance()->GetMousePosition().x < 430 && InputManager::GetInstance()->GetMousePosition().y < 80))
	{
		_poly->SetColor({ 0.9, 0.3, 0.2, 0.0 });
	}
	else
		_poly->SetColor({ 0.2, 0.6, 0.6, 0.3 });

	if (InputManager::GetInstance()->GetKey(VK_SHIFT))
	{
		Vector2 mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
		Vector3 mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
		Vector3 mouseWorldPosition = Matrix3x3::Mul(mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
		float mouseX = mouseWorldPosition.x;
		float mouseY = (-1) * mouseWorldPosition.y;

		_currentIndex.x = (int)(mouseX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
		_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - mouseY) / GridHeight;

		if (InputManager::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			_startIndex = _currentIndex;
		}

		if (InputManager::GetInstance()->GetKey(VK_LBUTTON))
		{
			if (!(_startIndex.x <= _currentIndex.x && _startIndex.y <= _currentIndex.y))
				return;

			_vVertices[0].x = GRID_STARTPOINT.x + GridWidth * _startIndex.x - GridWidth / 2;
			_vVertices[0].y = ((GRID_STARTPOINT.y - GridHeight * _startIndex.y) + (GRID_STARTPOINT.y - GridHeight * _currentIndex.y)) / 2;

			_vVertices[1].x = GRID_STARTPOINT.x + GridWidth * _currentIndex.x + GridWidth / 2;
			_vVertices[1].y = _vVertices[0].y;

			_poly->SetVertices(_vVertices);

			_poly->SetStrokeWidth((_currentIndex.y - _startIndex.y) * GridHeight + GridHeight);
		}
	}

	if (InputManager::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
		_vVertices[0] = _vVertices[1] = Vector2(0, 0);
		_poly->SetVertices(_vVertices);
	}

	if (InputManager::GetInstance()->GetKeyUp(VK_SHIFT))
	{
		_vVertices[0] = _vVertices[1] = Vector2(0, 0);
		_poly->SetVertices(_vVertices);
	}
}