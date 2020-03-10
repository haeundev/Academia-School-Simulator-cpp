#pragma once
#include "GgaetIp.h"

class SettingsButton : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	bool _check = false;

public:
	virtual void Update() override;
};