#pragma once
#include "GgaetIp.h"

class Department : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _descriptionBox;

public:
	virtual void Init() override;
	virtual void Update() override;
};