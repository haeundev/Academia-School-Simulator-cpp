#include "stdafx.h"

void PolygonDraw::Init()
{
	Direct2D::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &br);
}

void PolygonDraw::Render()
{
	if (!vertices.size() || !br)
		return;
	auto renderTarget = Direct2D::GetInstance()->GetRenderTarget();

	Matrix3x3 localToWorldMatrix = transform->GetLocalToWorldMatrix();
	if (object->GetCameraAffected())
		localToWorldMatrix = localToWorldMatrix * CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix();
	renderTarget->SetTransform(localToWorldMatrix.To_D2D1_Matrix_3x2_F());
	for (int i = 0; i < vertices.size(); i++)
	{
		int next = (i + 1) % vertices.size();
		D2D1_POINT_2F point1 = { vertices[i].x,vertices[i].y };
		D2D1_POINT_2F point2 = { vertices[next].x,vertices[next].y };
		renderTarget->DrawLine(point1, point2, br, strokeWidth);
	}
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void PolygonDraw::SetVertices(vector<Vector2> _vertices)
{
	vertices.clear();
	for (auto v : _vertices)
		vertices.push_back(Vector2(v.x, -v.y));
}

vector<Vector2> PolygonDraw::GetVertices()
{
	return vertices;
}

void PolygonDraw::SetColor(Color _color)
{
	if (br)
		br->Release();
	Direct2D::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(_color.r, _color.g, _color.b, _color.a), &br);
	color = _color;
}

void PolygonDraw::SetStrokeWidth(float _strokeWidth)
{
	strokeWidth = _strokeWidth;
}