#include "stdafx.h"
#include "CharacterIndex.h"

void CharacterIndex::Init()
{
	_characterPosition = object->GetTransform()->GetPosition();
	_characterPosition_V3 = Vector3(_characterPosition.x, _characterPosition.y, 1);
	_characterX = _characterPosition_V3.x;
	_characterY = _characterPosition_V3.y;

	_currentIndex.x = (int)(_characterX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - _characterY) / GridHeight;
}

void CharacterIndex::Update()
{
	_characterPosition = object->GetTransform()->GetPosition();
	_characterPosition_V3 = Vector3(_characterPosition.x, _characterPosition.y, 1);
	_characterX = _characterPosition_V3.x;
	_characterY = _characterPosition_V3.y;

	_currentIndex.x = (int)(_characterX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - _characterY) / GridHeight;
}