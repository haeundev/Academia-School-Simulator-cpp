#pragma once
#include "GgaetIp.h"

class GameScene : public Scene
{
private:
	vector<Object*> _vTiles;

public:
	virtual void Init() override;

	vector<Object*>& GetVTiles() { return _vTiles; }
};