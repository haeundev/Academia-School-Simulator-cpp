#include "stdafx.h"
#include "DrawZones.h"
#include "RealtimePoly.h"

void DrawZones::Init()
{
	// Zone을 만들면 이 맵에 있는 수를 올릴 예정.
	_mZones.insert(pair("Lounge", 0));
	_mZones.insert(pair("Office", 0));
	_mZones.insert(pair("Classroom", 0));
	_mZones.insert(pair("Cafeteria", 0));
	_mZones.insert(pair("Kitchen", 0));
	_mZones.insert(pair("Clinic", 0));
	_mZones.insert(pair("ArtRoom", 0));
	_mZones.insert(pair("ComputerLab", 0));
	_mZones.insert(pair("Library", 0));
	_mZones.insert(pair("MusicRoom", 0));
	_mZones.insert(pair("ScienceLab", 0));
	_mZones.insert(pair("Toilet", 0));

	_realtimePoly = Object::CreateObject();
	_realtimePoly->AddComponent<RealtimePoly>();
	_realtimePoly->GetComponent<RealtimePoly>()->SetVTilesLink(_vTiles);
}

void DrawZones::Update()
{
	Vector2 mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	Vector3 mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
	Vector3 mouseWorldPosition = Matrix3x3::Mul(mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
	float mouseX = mouseWorldPosition.x;
	float mouseY = (-1) * mouseWorldPosition.y;

	_currentIndex.x = (int)(mouseX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - mouseY) / GridHeight;


	if (InputManager::GetInstance()->GetKey('Z'))
	{
		if (!_sStoreZoneKey.size()) return;

		_realtimePoly->SetIsActive(true);

		if (InputManager::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			_startIndex = _currentIndex;
		}
		if (InputManager::GetInstance()->GetKeyUp(VK_LBUTTON))
		{
			_endIndex = _currentIndex;

			DrawZone();
		}
	}
	else
	{
		_realtimePoly->SetIsActive(false);
	}
}

void DrawZones::DrawZone()
{
	Vector2 _startRealPos;
	_startRealPos.x = GRID_STARTPOINT.x + GridWidth * _startIndex.x - GridWidth / 2;
	_startRealPos.y = GRID_STARTPOINT.y - GridHeight * _startIndex.y;
	Vector2 _endRealPos;
	_endRealPos.x = GRID_STARTPOINT.x + GridWidth * _endIndex.x + GridWidth / 2;
	_endRealPos.y = GRID_STARTPOINT.y - GridHeight * _endIndex.y;

	if (_startIndex.y < _endIndex.y)
	{
		_vVertices.push_back(Vector2(_startRealPos.x, _startRealPos.y - abs(_startRealPos.y - _endRealPos.y) / 2));
		_vVertices.push_back(Vector2(_endRealPos.x, _startRealPos.y - abs(_startRealPos.y - _endRealPos.y) / 2));
	}
	else
	{
		_vVertices.push_back(Vector2(_startRealPos.x, _startRealPos.y + abs(_endRealPos.y - _startRealPos.y) / 2));
		_vVertices.push_back(Vector2(_endRealPos.x, _startRealPos.y + abs(_endRealPos.y - _startRealPos.y) / 2));
	}

	Object* newZone = Object::CreateObject();
	newZone->SetName(_sStoreZoneKey.top());
	auto zonePoly = newZone->AddComponent<PolygonDraw>();
	zonePoly->SetVertices(_vVertices);
	zonePoly->SetColor({ 1,1,1, 0.05 });
	zonePoly->SetStrokeWidth(abs(_endIndex.y - _startIndex.y) * GridHeight + GridHeight);
	zonePoly->SetDepth((int)ZORDER::ZONE);

	Object* zoneText = Object::CreateObject(newZone);
	zoneText->AddComponent<Text>();
	zoneText->GetComponent<Text>()->CreateText(StringToWstring(_sStoreZoneKey.top()), L"Times New Roman", L"ko-KR", { 0,0,0,0.6 }, 50, 400, 100);
	zoneText->GetComponent<Text>()->SetDepth((int)ZORDER::ZONE_TEXT);

	if (_startIndex.y < _endIndex.y)
	{
		zoneText->GetTransform()->SetPosition(Vector2((_startRealPos.x + _endRealPos.x) / 2 + GridWidth, _startRealPos.y - GridHeight - abs(_startRealPos.y - _endRealPos.y) / 2));
	}
	else
	{
		zoneText->GetTransform()->SetPosition(Vector2((_startRealPos.x + _endRealPos.x) / 2 + GridWidth, _startRealPos.y - GridHeight + abs(_startRealPos.y - _endRealPos.y) / 2));
	}

	_vVertices.clear();

	_mZones[_sStoreZoneKey.top()]++;

	// 모든 Zone의 개수가 1 이상이면 입학 가능.
	for (auto m : _mZones)
	{
		if (m.second != 0)
		{
			_admissionsReady = true;
		}
	}
}