#pragma once
#include "GgaetIp.h"
#include "Tile.h"

struct tagObjectInfo
{
	ATTRIBUTE attribute;
	int cost;
};

class ObjectData : public Script
{
private:

public:
	virtual void Init() override;

	map<string, tagObjectInfo> info;
	map<string, tagObjectInfo> GetMAttributeData() { return info; }
};