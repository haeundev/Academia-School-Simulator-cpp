#pragma once
#include "GgaetIp.h"
#include "Observe.h"
#include "AStar.h"

enum class NurseState
{
	TO_DESTINATION,
	WORKING
};

class NurseMove : public Script, public Observe
{
private:
	Transform* _transform;
	Sprite* _sprite;

	AStar* _star;
	vector<Object*>* _vTiles;
	Animator* _animator;
	float _characterAngle;

	vector<Vector2> _vRoute;

	Vector2 _characterNowIndex;
	Vector2 _characterNowPos;
	Vector2 _startIndex;
	Vector2 _nextIndex;

	int _nowArrayNum;

	NurseState _nurseState = NurseState::TO_DESTINATION;
	int _idleCount = 0;
	bool _haveIdlePath = false;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetVTilesLink(vector<Object*>* v) { _vTiles = v; }

	virtual void OnNotify(MTYPE type, string event) override;

	void Move();
	void IdleMove();
	void SetDirection();
};