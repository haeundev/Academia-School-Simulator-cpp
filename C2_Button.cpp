#include "stdafx.h"
#include "C2_Button.h"
#include "C3_Window.h"
#include "LinkButton_C2B_C3W.h"

void C2_Button::Init()
{
	_sprite = object->AddComponent<Sprite>();
	_transform = object->GetTransform();

	object->AddComponent<BoxCollider>();

	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-103, 0));
	vVertices.push_back(Vector2(103, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(28);
	object->GetComponent<PolygonDraw>()->SetDepth(0);

	// C3
	_c3Window = Object::CreateObject();
	_c3Window->SetName(object->GetName());
	_c3Window->SetTag(object->GetTag());
	_c3Window->AddComponent<C3_Window>();
	_c3Window->GetComponent<C3_Window>()->SetC3WindowTag(object->GetName());
	_c3Window->SetIsActive(false);

	// C2 버튼을 누르면 C3_Window가 열린다.
	object->AddComponent<LinkButton_C2B_C3W>();
	object->GetComponent<LinkButton_C2B_C3W>()->SetLink(_c3Window);
}

void C2_Button::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.1 });
	}
	else
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0 });
	}
}