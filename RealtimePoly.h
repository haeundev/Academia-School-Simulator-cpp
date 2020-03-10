#pragma once
#include "GgaetIp.h"

class RealtimePoly : public Script
{
private:
	PolygonDraw* _poly;

	vector<Vector2> _vVertices;
	vector<Object*>* _vTiles;

	Vector2 _currentIndex;

	Vector2 _startIndex;
	Vector2 _endIndex;

	Vector2 _dimension;

	Transform* _transform;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetVTilesLink(vector<Object*>* vt) { _vTiles = vt; }
};