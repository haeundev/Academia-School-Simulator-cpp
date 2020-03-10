#pragma once
#include "GgaetIp.h"

class TopBar;
class AdmissionWindow;
class StartSchoolYear : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	TopBar* _topBar;
	AdmissionWindow* _admissionWindow;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetTopBarLink(TopBar* t) { _topBar = t; }
	void SetAdmissionWindowLink(AdmissionWindow* w) { _admissionWindow = w; }
};