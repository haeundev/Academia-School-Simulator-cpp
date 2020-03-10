#pragma once
#include "GgaetIp.h"
#include "Observe.h"
#include "AStar.h"

class Faculty : public Script, public Observe
{
private:
	Transform* _transform;
	Sprite* _sprite;

	AStar* _star;
	vector<Object*> _vTiles;
	Animator* _animator;
	float _characterAngle;

	vector<Vector2> _vRoute;

	Vector2 _characterNowIndex;
	Vector2 _characterNowPos;
	Vector2 _startIndex;
	Vector2 _nextIndex;

	int _nowArrayNum;

public:

};