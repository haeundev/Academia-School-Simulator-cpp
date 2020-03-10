#include "stdafx.h"
#include "Department.h"
#include "HireWindow.h"
#include "LinkButton.h"

void Department::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("Management/Department.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);

	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(1490, -810));

	object->AddComponent<BoxCollider>();

	// Polydraw
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-100, 0));
	vVertices.push_back(Vector2(100, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(35);
	object->GetComponent<PolygonDraw>()->SetDepth((int)ZORDER::POLY_ON_UI);

	Object* hireWindow = Object::CreateObject();
	hireWindow->AddComponent<HireWindow>();
	hireWindow->SetIsActive(false);

	object->AddComponent<LinkButton>();
	object->GetComponent<LinkButton>()->SetLink(hireWindow);

	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/Description/Department.png"));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_descriptionBox->GetTransform()->SetPosition(Vector2(1218, -795));
	_descriptionBox->SetCameraAffected(false);
}

void Department::Update()
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