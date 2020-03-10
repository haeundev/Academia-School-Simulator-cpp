#pragma once
#include "GgaetIp.h"
#include "Observe.h"
#include "AStar.h"

enum class FacultyState
{
	TO_DESTINATION,
	TEACHING
};

class Schedule;
class FacultyMove : public Script, public Observe
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

	Object* _teacherBook;
	Object* _teacherChalk;
	float _chalkAngle = 0;

	Schedule* _schedule;

	FacultyState _facultyState = FacultyState::TO_DESTINATION;
	int _idleCount = 0;
	bool _haveIdlePath = false;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetVTilesLink(vector<Object*>* v) { _vTiles = v; }
	void SetMZonesLink(map<string, int> m) { _mZones = m; }
	void SetScheduleLink(Schedule* s) { _schedule = s; }

	virtual void OnNotify(MTYPE type, string event) override;

	void Move();
	void IdleMove();
	void SetDirection();
};