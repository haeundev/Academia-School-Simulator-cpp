#include "stdafx.h"
#include "DrawGrid.h"

void DrawGrid::Init()
{
	DrawLines();
}

void DrawGrid::DrawLines()
{
	vector<Vector2> vHorizontalPos;
	vHorizontalPos.push_back(Vector2(GRID_STARTPOINT.x + 64, GRID_STARTPOINT.y));
	vHorizontalPos.push_back(Vector2(-DesignResolution.x / 2 + 64 + TotalGridX * GridWidth, GRID_STARTPOINT.y));
	vector<Vector2> vVerticalPos;
	vVerticalPos.push_back(Vector2(GRID_STARTPOINT.x, GRID_STARTPOINT.y - 64));
	vVerticalPos.push_back(Vector2(GRID_STARTPOINT.x, GRID_STARTPOINT.y - TotalGridY * GridHeight - 64));

	for (int i = 0; i < TotalGridX + 1; i++)
	{
		Object* horizontalLine = Object::CreateObject(object);
		horizontalLine->AddComponent<PolygonDraw>()->SetVertices(vHorizontalPos);

		horizontalLine->GetTransform()->SetPosition(Vector2(-GridWidth, - i * GridWidth + GridHeight/2));
		horizontalLine->GetComponent<PolygonDraw>()->SetColor({1, 1, 1, 0.5});
	}
	for (int i = 0; i < TotalGridY + 1; i++)
	{
		Object* verticalLine = Object::CreateObject(object);
		verticalLine->AddComponent<PolygonDraw>()->SetVertices(vVerticalPos);
		
		verticalLine->GetTransform()->SetPosition(Vector2(i * GridHeight - GridWidth/2, GridHeight));
		verticalLine->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.5 });
	}
}