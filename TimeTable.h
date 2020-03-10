#pragma once
#include "GgaetIp.h"
#include "Observe.h"

class TimeTable : public Script, public Observe
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _descriptionBox;

public:
	virtual void Init() override;
	virtual void Update() override;

	virtual void OnNotify(MTYPE type, string event) override;
};