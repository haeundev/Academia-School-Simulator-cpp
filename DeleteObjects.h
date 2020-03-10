#pragma once
#include "GgaetIp.h"

class DeleteObjects : public Script
{
private:
	vector<Object*>* _vTiles;
	vector<Object*> _vWalls;

	Sprite* _sprite;

	Vector2 _mousePosition;
	Vector3 _mousePosition_V3;
	Vector3 _mouseWorldPosition;
	float _mouseX;
	float _mouseY;

	Vector2 _currentIndex;

	bool _isDeleteMode = false;


public:
	virtual void Init() override;
	virtual void Update() override;

	void SetVTilesLink(vector<Object*>* vt) { _vTiles = vt; }
	void SetVWallsLink(vector<Object*> vw) { _vWalls = vw; }

	bool GetIsDeleteMode() { return _isDeleteMode; }
	void SetIsDeleteMode(bool tf) { _isDeleteMode = tf; }

};