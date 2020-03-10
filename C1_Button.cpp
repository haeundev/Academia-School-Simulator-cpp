#include "stdafx.h"
#include "C1_Button.h"
#include "LinkButton.h"
#include "C1_Window.h"
#include "C2_Window.h"

void C1_Button::Init()
{
	_sprite = object->AddComponent<Sprite>();
	_transform = object->GetTransform();

	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/C1_Buttons/" + object->GetName() + ".png"));
	_sprite->SetDepth(5);
	object->AddComponent<BoxCollider>();

	// Polydraw
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-100, 0));
	vVertices.push_back(Vector2(100, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(40);
	object->GetComponent<PolygonDraw>()->SetDepth((int)ZORDER::POLY_ON_UI);

	// C2
	_c2Window = Object::CreateObject();
	_c2Window->AddComponent<Sprite>();
	_c2Window->AddComponent<C2_Window>();
	_c2Window->GetComponent<C2_Window>()->SetC2WindowTag(object->GetName());
	_c2Window->SetName(object->GetName());
	_c2Window->GetComponent<C2_Window>()->SetC1WindowLink(object->GetParent());
	_c2Window->SetIsActive(false);
	_c2Window->GetComponent<Sprite>()->SetLayer(Layer::CreateLayer(Vector2(250, 303), Vector2(-470, -395)));

	// C1 버튼을 누르면 C2_Window가 열린다.
	object->AddComponent<LinkButton>();
	object->GetComponent<LinkButton>()->SetLink(_c2Window);

	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/Description/" + object->GetName() + ".png"));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);

	if (object->GetName() == "Zones")
		_descriptionBox->GetTransform()->SetPosition(Vector2(338, -720));
	if (object->GetName() == "Build")
		_descriptionBox->GetTransform()->SetPosition(Vector2(355, -760));
	if (object->GetName() == "Objects")
		_descriptionBox->GetTransform()->SetPosition(Vector2(363, -798));
	
	_descriptionBox->SetCameraAffected(false);
}

void C1_Button::Update()
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