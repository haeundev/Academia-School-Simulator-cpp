#pragma once
#include "GgaetIp.h"

class C2_Button : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _c3Window;

public:
	virtual void Init() override;
	virtual void Update() override;
};