#pragma once
#include "GgaetIp.h"

class C1_Window;
class C1_Button : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _c2Window;
	Object* _c1Window;

	Object* _descriptionBox;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetC1WindowLink(Object* w) { _c1Window = w; }
};