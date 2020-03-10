#include "stdafx.h"
#include "DebugDraw.h"
#include "Direct2D.h"

DebugDraw* DebugDraw::GetInstance()
{
	static DebugDraw* instance = new DebugDraw();
	instance->SetFlags(e_shapeBit);
	return instance;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Direct2D::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0, 0, 1, 1), &br);
	for (int i = 0; i < vertexCount; i++)
	{
		float p2w = PhysicsManager::GetInstance()->GetPhysicsWorldToWorld();
		Vector2 cameraPosition = CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetPosition() + Vector2(0,DesignResolution.y );
		D2D_POINT_2F point1 = D2D1::Point2(vertices[i].x*p2w+ cameraPosition.x , vertices[i].y*p2w + cameraPosition.y );
		D2D_POINT_2F point2;
		if (i + 1 == vertexCount)\
			point2 = D2D1::Point2(vertices[0].x*p2w + cameraPosition.x , vertices[0].y*p2w + cameraPosition.y );
		else
			point2 = D2D1::Point2(vertices[i + 1].x*p2w + cameraPosition.x , vertices[i + 1].y*p2w + cameraPosition.y );
		Direct2D::GetInstance()->GetRenderTarget()->DrawLine(point1, point2, br);
	}
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{

}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}

void DebugDraw::DrawTransform(const b2Transform& xf)
{

}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{

}
