#pragma once
#include "GgaetIp.h"

class LinkButton : public Script
{
private:
	Object* linked;

public:
	virtual void Init();
	virtual void Update();
	virtual void OnMouseDown() override;

	void SetLink(Object* obj) { linked = obj; }
};