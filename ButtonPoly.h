#pragma once
#include "GgaetIp.h"

class ButtonPoly : public Script
{
private:
	Sprite* _sprite;

public:
	virtual void Init() override;
	virtual void Update() override;
};