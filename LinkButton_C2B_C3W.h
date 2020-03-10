#pragma once
#include "GgaetIp.h"

class LinkButton_C2B_C3W : public Script
{
private:
	Object* linked;
	//Object* c3Window;

public:
	virtual void Init();
	virtual void Update();
	virtual void OnMouseDown() override;

	void SetLink(Object* obj) { linked = obj; }
	//void SetC3WindowLink(Object* c3w) { c3Window = c3w; }
};