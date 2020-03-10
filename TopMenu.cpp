#include "stdafx.h"
#include "TopMenu.h"

void TopMenu::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(Image::CreateImage("UI/TopMenu/Bar.png"));

	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(800, -18));
}

void TopMenu::Update()
{
}

void TopMenu::OnMouseDown()
{
}
