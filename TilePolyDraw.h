#pragma once
#include "GgaetIp.h"

class FollowMouseSprite;
class TilePolyDraw : public Script
{
private:
	vector<Vector2> _vVertices;
	vector<Object*>*_vTiles;
	Vector2 _currentIndex;

	Transform* _transform;
	FollowMouseSprite* _followMouseSprite;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetVTilesLink(vector<Object*>* vt) { _vTiles = vt; }
	void SetFollowMouseSpriteLink(FollowMouseSprite* s) { _followMouseSprite = s; }
};