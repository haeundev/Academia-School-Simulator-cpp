#pragma once
#include "GgaetIp.h"

class TopBar;
class Admissions : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _descriptionBox;
	Object* _admissionWindow;

	TopBar* _topBar;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetTopBarLink(TopBar* t) { _topBar = t; }
	Object* GetAdmissionWindow() { return _admissionWindow; }
};