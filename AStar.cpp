#include "stdafx.h"
#include "AStar.h"
#include "GameScene.h"

void AStar::AddOpenList()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int nowIndex = (currentIndex.x - 1 + j) + TotalGridX * (currentIndex.y - 1 + i);

			//����ó�� 
			if (nowIndex < 0 || nowIndex > vTotal.size() - 1) continue;
			if ((currentIndex.x == 0 && j == 0)|| (currentIndex.x == TotalGridX - 1 && j == 2))  continue;
			if ((currentIndex.y == 0 && i == 0) || (currentIndex.y == TotalGridY - 1 && i == 2)) continue;
			if (i == 1 && j == 1) continue;

			if (!allowDiagonalMove)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 2))
					continue;
			}

			Tile* current = vTotal[nowIndex]->GetComponent<Tile>();


			//�ڽ�Ʈ ó�� 
			Vector2 temp = vTotal[nowIndex]->GetTransform()->GetPosition() - vTotal[targetIndex.x + TotalGridX * targetIndex.y]->GetTransform()->GetPosition();
			float H = temp.Magnitude();

			Vector2 temp2 = vTotal[nowIndex]->GetTransform()->GetPosition() - vTotal[currentIndex.x + TotalGridX * currentIndex.y]->GetTransform()->GetPosition();
			float G = temp2.Magnitude() + vTotal[currentIndex.x + TotalGridX * currentIndex.y]->GetComponent<Tile>()->GetCostFromStart();


			//�ʿ��� �� �ڽ�Ʈ ������Ʈ 
			if (current->GetIsOpen())
			{
				if (G + H < current->GetTotalCost())
				{
					current->SetTotalCost(G + H);
					current->SetParent(vTotal[currentIndex.x + TotalGridX * currentIndex.y]->GetComponent<Tile>());
				}

				continue;
			}
			if (current->GetAttribute() == ATTRIBUTE::TILE_WALL) continue;

			if (current->GetFlag() == 1 || current->GetFlag() == 2 || current->GetFlag() == 4 || current->GetFlag() == 8)
			{
				{
					if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 2))
						continue;
				}
			}

			//�������� �ʾҴٸ� �ڽ�Ʈ �����ְ� OPEN LIST�� Ǫ�� 
			current->SetCostFromStart(G);
			current->SetCostToGoal(H);
			current->SetTotalCost(G + H);
			current->SetParent(vTotal[currentIndex.x + TotalGridX * currentIndex.y]->GetComponent<Tile>());
			current->SetIsOpen(true);

			vOpen.push_back(vTotal[nowIndex]);
		}
	}
}

void AStar::FindPath()
{
	//���� 
	vOpen.clear();
	vClosed.clear();
	path.clear();

	for (int i = 0; i < vTotal.size(); i++)
	{
		if (vTotal[i]->GetComponent<Tile>()->GetAttribute() == ATTRIBUTE::TILE_WALL)
			continue;
		vTotal[i]->GetComponent<Tile>()->SetAttribute(ATTRIBUTE::TILE_NONE);
		vTotal[i]->GetComponent<Tile>()->SetIsOpen(false);
	}

	vClosed.push_back(vTotal[startIndex.x + TotalGridX * startIndex.y]);
	vTotal[startIndex.x + TotalGridX * startIndex.y]->GetComponent<Tile>()->SetIsOpen(true);
	currentIndex = startIndex;

	int count = 0;
	
	while (true)
	{
		//�� ã�� �Ϸ� 
		if (targetIndex == currentIndex)
		{
			Vector2 index = targetIndex;
			path.push_back(vTotal[index.x + TotalGridX * index.y]);
			while (true)
			{
				Vector2 delta = vTotal[index.x + TotalGridX * index.y]->GetTransform()->GetPosition();
				Vector2 startPos = vTotal[startIndex.x + TotalGridX * startIndex.y]->GetTransform()->GetPosition();

				if (sqrt((delta.x - startPos.x) * (delta.x - startPos.x) + (delta.y - startPos.y) * (delta.y - startPos.y)) <= sqrt(GridWidth * GridHeight * 2))
				{
					break;
				}
				if (index == startIndex)
					break;

				index = vTotal[index.x + TotalGridX * index.y]->GetComponent<Tile>()->GetParent()->GetIndex();
				path.push_back(vTotal[index.x + TotalGridX * index.y]);
			}
			return;
		}

		AddOpenList();

		//���� ó�� 
		if (!vOpen.size())
			return;

		int cost = 100000;
		int index = 0;
		Vector2 index2 = Vector2::zero;

		//OPEN���� ���� COST�� ���� ���� CLOSED �� ���ϰ� OPEN������ ���� 
		for (int i = 0; i < vOpen.size(); i++)
		{
			if (vOpen[i]->GetComponent<Tile>()->GetTotalCost() < cost)
			{
				cost = vOpen[i]->GetComponent<Tile>()->GetTotalCost();
				index = i;
			}
		}
		vClosed.push_back(vOpen[index]);
		vOpen.erase(vOpen.begin() + index);

		//OPEN LIST ������Ʈ�� ���� currentindex ������Ʈ 
		currentIndex = vClosed[vClosed.size() - 1]->GetComponent<Tile>()->GetIndex();
	}
}