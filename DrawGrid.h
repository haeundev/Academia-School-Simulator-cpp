#pragma once
#include "GgaetIp.h"

class DrawGrid : public Script
{
private:
	Vector2 _gridStartPoint;

public:
	virtual void Init() override;

	virtual void DrawLines();
	void SetGridStartPoint(Vector2 pos) { _gridStartPoint = pos; }
};