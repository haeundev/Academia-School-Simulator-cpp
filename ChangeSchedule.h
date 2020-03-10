#pragma once
#include "GgaetIp.h"
#include "Observed.h"

class ChangeSchedule : public Script, public Observed
{
private:
	Transform* _transform;
	Sprite* _sprite;

public:
	virtual void OnMouseDown() override;
};