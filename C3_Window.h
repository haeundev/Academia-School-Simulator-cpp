#pragma once
#include "GgaetIp.h"

class C3_Window : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	string _C3WindowTag;

	vector<string> _vButtonsForC3;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetC3WindowTag(string s) { _C3WindowTag = s; }
	void AddButtons();
};