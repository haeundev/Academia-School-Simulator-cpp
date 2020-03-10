#pragma once
#include "GgaetIp.h"

class SettingsWindow : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	vector<string> _vButtonNames;

public:
	virtual void Init() override;
	
	void AddButtons();
};