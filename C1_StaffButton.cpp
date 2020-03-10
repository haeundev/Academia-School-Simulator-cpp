#include "stdafx.h"
#include "C1_StaffButton.h"
#include "C3_Window.h"
#include "C3_StaffWindow.h"
#include "LinkButton.h"

void C1_StaffButton::Init()
{
	object->AddComponent<BoxCollider>();

	_sprite = object->AddComponent<Sprite>();
	_transform = object->GetTransform();

	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/C1_Buttons/" + object->GetName() + ".png"));
	_sprite->SetDepth(5);

	// Polydraw
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-100, 0));
	vVertices.push_back(Vector2(100, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(40);
	object->GetComponent<PolygonDraw>()->SetDepth(0);

	// C2 건너뛰고 C3
	_c3Window = Object::CreateObject();
	_c3Window->SetName(object->GetName());
	_c3Window->AddComponent<C3_StaffWindow>();
	_c3Window->SetIsActive(false);

	// C2 버튼을 누르면 C3_Window가 열린다.
	object->AddComponent<LinkButton>();
	object->GetComponent<LinkButton>()->SetLink(_c3Window);

	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/Description/Staff.png"));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_descriptionBox->GetTransform()->SetPosition(Vector2(342, -836));
	_descriptionBox->SetCameraAffected(false);
}

void C1_StaffButton::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.1 });
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0.85);
	}
	else
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0 });
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
	}
}