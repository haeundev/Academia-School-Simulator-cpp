#pragma once
#include "GgaetIp.h"

class Settings : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _settingsWindow;

	Object* _descriptionBox;

public:
	virtual void Init() override;
	virtual void Update() override;
};