#pragma once
#include "stdafx.h"
#include "GgaetIp.h"

class Observe abstract
{
public:
	virtual void OnNotify(MTYPE type, string event) = 0;
};