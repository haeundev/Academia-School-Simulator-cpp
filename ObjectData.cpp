#include "stdafx.h"
#include "ObjectData.h"
#include  <fstream>
#pragma warning (disable:4996)

void ObjectData::Init()
{
	string nowString;
	vector<string> nowData;

	fstream stream;
	stream.open("Resources/Data/AttributeData.csv", ios::in);

	while (true)
	{
		stream >> nowString;
		if (stream.eof())
			break;
		char* data = strtok(const_cast<char*>(nowString.c_str()), ",");
		for (; data != NULL; data = strtok(NULL, ","))
			nowData.push_back(data);

		tagObjectInfo nowInfo;
		nowInfo.cost = atoi(nowData[2].c_str());

		if (nowData[1] == "TILE_FLOOR")
			nowInfo.attribute = ATTRIBUTE::TILE_FLOOR;
		else if (nowData[1] == "TILE_WALL")
			nowInfo.attribute = ATTRIBUTE::TILE_WALL;
		else if (nowData[1] == "TILE_OBJECT_BLOCKED")
			nowInfo.attribute = ATTRIBUTE::TILE_OBJECT_BLOCKED;
		else if (nowData[1] == "TILE_OBJECT_OPEN")
			nowInfo.attribute = ATTRIBUTE::TILE_OBJECT_OPEN;
		else if (nowData[1] == "TILE_NONE")
			nowInfo.attribute = ATTRIBUTE::TILE_NONE;

		info[nowData[0]] = nowInfo;

		nowData.clear();
	}

	stream.close();
}