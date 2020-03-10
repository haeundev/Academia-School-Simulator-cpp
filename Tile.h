#pragma once
#include "GgaetIp.h"

enum class ATTRIBUTE
{
	TILE_NONE,
	TILE_FLOOR,
	TILE_WALL,
	TILE_OBJECT_OPEN,
	TILE_OBJECT_BLOCKED
};



class Tile : public Script
{
private:
	vector<Vector2> _vVertices;

	Vector2 _index;
	
	shared_ptr<Image> image;

	ATTRIBUTE _attribute;

	unsigned char myflags = 0;				// 플래그 저장 변수   

	const unsigned char option0 = 1 << 0;	// 0001   1
	const unsigned char option1 = 1 << 1;	// 0010   2
	const unsigned char option2 = 1 << 2;	// 0100   4
	const unsigned char option3 = 1 << 3;	// 1000   8

	float totalCost = 2500;
	float costFromStart = 2500;
	float costToGoal = 2500;

	bool isOpen = false;

	Tile* parent;

public:
	void SetIndex(Vector2 idx)	{ _index = idx; }
	Vector2 GetIndex()			{ return _index; }

	void SetAttribute(ATTRIBUTE att)		{ _attribute = att; }
	ATTRIBUTE GetAttribute()				{ return _attribute; }

	void FlagLeftOn()		{ myflags |= option0; }
	void FlagTopOn()		{ myflags |= option1; }
	void FlagRightOn()		{ myflags |= option2; }
	void FlagBottomOn()		{ myflags |= option3; }

	void FlagLeftOff()		{ myflags &= ~option0; }
	void FlagTopOff()		{ myflags &= ~option1; }
	void FlagRightOff()		{ myflags &= ~option2; }
	void FlagBottomOff()	{ myflags &= ~option3; }

	unsigned char GetFlag()				{ return myflags; }
	void SetFlag(unsigned char c)		{ myflags = c; }

	/////////////////////////////

	void SetParent(Tile* parent) { this->parent = parent; }
	void SetIsOpen(bool isOpen) { this->isOpen = isOpen; }

	void SetTotalCost(float cost) { this->totalCost = cost; }
	void SetCostFromStart(float cost) { this->costFromStart = cost; }
	void SetCostToGoal(float cost) { this->costToGoal = cost; }

	Tile* GetParent() { return parent; }
	bool GetIsOpen() { return isOpen; }

	float GetTotalCost() { return totalCost; }
	float GetCostFromStart() { return costFromStart; }
	float GetCostToGoal() { return costToGoal; }
};