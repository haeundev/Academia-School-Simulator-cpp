#pragma once
#include "GgaetIp.h"

class ToDoWindow : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

public:
	virtual void Init() override;

	void AddList();
};