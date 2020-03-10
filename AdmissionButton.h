#pragma once
#include "GgaetIp.h"

class AdmissionButton : public Script
{
private:
	int count = 0;

public:
	virtual void Init() override;
	virtual void Update() override;
};