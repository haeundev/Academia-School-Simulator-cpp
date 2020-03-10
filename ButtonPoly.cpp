#include "stdafx.h"
#include "ButtonPoly.h"

void ButtonPoly::Init()
{
	_sprite = object->GetComponent<Sprite>();

	// Polydraw
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-_sprite->GetFrameSize().x / 2, 0));
	vVertices.push_back(Vector2(_sprite->GetFrameSize().x / 2, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(_sprite->GetFrameSize().y);
	object->GetComponent<PolygonDraw>()->SetDepth((int)ZORDER::POLY_ON_UI);
}

void ButtonPoly::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.15 });
	}
	else
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0 });
	}
}