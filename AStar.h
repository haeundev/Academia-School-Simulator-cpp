#pragma once
#include "GgaetIp.h"
#include "Tile.h"

class AStar : public Script
{
private:
	vector<Object*> vTotal;
	vector<Object*> vOpen;
	vector<Object*> vClosed;
	vector<Object*> path;

	bool _isStart = false;
	bool allowDiagonalMove = true;

	Vector2 startIndex;
	Vector2 currentIndex;
	Vector2 targetIndex;

	int count = 0;
	int pathSize = 0;

public:
	void SetVTilesLink(vector<Object*> v) 
{ 
		vTotal = v; 
		int a = 10;
	}

	void AddOpenList();
	void FindPath();

	void SetStartIndex(Vector2 startIndex) { this->startIndex = startIndex; }

	void SetAllowDiagonalMove(bool allow) { allowDiagonalMove = allow; }

	vector<Vector2> GetPath(Vector2 startIndex, Vector2 targetIndex)
	{
		vector<Vector2> vPath;

		this->startIndex = startIndex;
		this->targetIndex = targetIndex;
		vClosed.push_back(vTotal[targetIndex.x + TotalGridX * targetIndex.y]);
		Tile* temp = vTotal[targetIndex.x + TotalGridX * targetIndex.y]->GetComponent<Tile>();
		temp->SetIsOpen(true);
		temp->SetCostFromStart(0);
		temp->SetCostToGoal(0);
		temp->SetTotalCost(0);
		temp->SetParent(NULL);

		FindPath();

		for (int i = path.size() - 1; i >= 0; i--)
		{
			vPath.push_back(path[i]->GetComponent<Tile>()->GetIndex());
		}

		return vPath;
	}
};