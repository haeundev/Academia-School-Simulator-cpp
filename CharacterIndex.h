#pragma once
#include "GgaetIp.h"

class CharacterIndex : public Script
{
private:

	Vector2 _characterPosition;
	Vector3 _characterPosition_V3;
	Vector3 _characterWorldPosition;
	float _characterX;
	float _characterY;

	Vector2 _currentIndex;

public:
	virtual void Init() override;
	virtual void Update() override;

	Vector2 GetIndex() { return _currentIndex; }
	void SetIndex(Vector2 v) { _currentIndex = v; }
};