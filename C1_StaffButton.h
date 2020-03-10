#pragma once
#include "GgaetIp.h"

class C1_StaffButton : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;
	Object* _c3Window;
	Object* _descriptionBox;

public:
	virtual void Init() override;
	virtual void Update() override;
};