#pragma once
#include "GgaetIp.h"

class ScheduleWindow;
class Schedule : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _descriptionBox;
	Object* _scheduleWindow;

public:
	virtual void Init() override;
	virtual void Update() override;

	Object* GetScheduleWindow() { return _scheduleWindow; }
};