#pragma once
#include "GgaetIp.h"
#include "Observe.h"

class ScheduleWindow : public Script, public Observe
{
private:
	Transform* _transform;
	Sprite* _sprite;

	vector<string> _vPeriods;

	vector<Object*> _vOrder;

	vector<vector<Vector2>> _vPosPerPeriod_Student;


public:
	virtual void Init() override;
	virtual void OnNotify(MTYPE mtype, string event) override;

	void SetButtons();

	vector<string> GetVPeriods() { return _vPeriods; }
	vector<Object*> GetVOrder() { return _vOrder; }
	vector<vector<Vector2>> GetVPosPerPeriodStudent() { return _vPosPerPeriod_Student; }
};