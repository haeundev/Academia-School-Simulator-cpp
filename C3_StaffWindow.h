#pragma once
#include "GgaetIp.h"

class C3_StaffWindow : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	string _C3WindowTag;

	vector<string> _vButtonsForC3;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnMouseDown() override;

	void AddButtons();
	void StopZoomAndJustScroll();
};