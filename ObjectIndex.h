#pragma once
#include "GgaetIp.h"

class ObjectIndex :	public Script
{
private:
	Vector2 _index;

public:
	void SetIndex(Vector2 idx) { _index = idx; }
	Vector2 GetIndex() { return _index; }

};