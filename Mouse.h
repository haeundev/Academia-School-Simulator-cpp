#pragma once
#include "GgaetIp.h"

class Mouse : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

public:
	virtual void Init() override;
	virtual void Update() override;
};