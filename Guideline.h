#pragma once
#include "GgaetIp.h"

class Guideline : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

public:
	virtual void Update() override;
};