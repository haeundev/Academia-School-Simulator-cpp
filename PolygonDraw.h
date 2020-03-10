#pragma once
#include "DrawComponent.h"

class PolygonDraw : public DrawComponent
{
private:
	vector<Vector2> vertices;
	float strokeWidth = 1;
	ID2D1SolidColorBrush* br;
	Color color = { 1,1,1,1 };
public:
	virtual void Init() override;
	virtual void Render() override;

	void SetVertices(vector<Vector2> _vertices);
	vector<Vector2> GetVertices();

	void SetColor(Color _color);
	void SetStrokeWidth(float _strokeWidth);
};