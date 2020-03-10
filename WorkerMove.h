#pragma once
#include "GgaetIp.h"
#include "AStar.h"
#include "CharacterManager.h"
#include <queue>

enum class WorkerState
{
	GOING,
	UNDER_CONSTRUCTION,
	RETURNING,
	AT_LOUNGE
};

class MapTool;
class WorkerMove : public Script
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

	map<string, int> _mZones;

	MapTool* _mapTool;

	bool _havePath = false;
	bool _haveIdlePath = false;
	bool _havePathToLounge = false;
	int _workDoneCount = 0;

	CharacterManager* _characterManager;

	Vector2 _loungePosition;

	WorkerState _workerState = WorkerState::RETURNING;

	int count2 = 0;
	int _idleCount = 0;

	Object* _hands;
	Object* _activity;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetVTilesLink(vector<Object*>* v) { _vTiles = v; }
	void SetMZonesLink(map<string, int> m) { _mZones = m; }
	void SetMapToolLink(MapTool* m) { _mapTool = m; }

	void Move();
	void IdleMove();
	void SetDirection();
};