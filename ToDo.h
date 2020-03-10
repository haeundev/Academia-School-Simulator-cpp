#pragma once
#include "GgaetIp.h"

class ToDo : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _todoWindow;
	Object* _descriptionBox;

public:
	virtual void Init() override;
	virtual void Update() override;
};