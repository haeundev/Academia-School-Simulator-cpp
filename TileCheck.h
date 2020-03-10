#pragma once
#include "GgaetIp.h"

class TileMap;

class TileCheck : public Script
{
private:
	vector<Object*> vTotal;
	vector<Object*> vTemp;

	Object* map;

	int index_X = 0;
	int index_Y = 0;

	Vector2 dimension;

	Object* newBuilding;
	Sprite* newBuildingSprite;


public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnMouseDown() override;

	void DrawTile();

	Vector2 GetMouseIndex() { return Vector2(index_X, index_Y); }
	vector<Object*> GetvTotal() { return vTotal; }
	void SetMouseIndex(Vector2 index){ index_X = index.x; index_Y = index.y;}
	void SetLink(Object* map) { this->map = map; }
	void SetLinkToBuilding(Object* newBuilding) { this->newBuilding = newBuilding; }
};

