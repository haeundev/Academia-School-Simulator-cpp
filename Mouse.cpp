#include "stdafx.h"
#include "Mouse.h"

void Mouse::Init()
{
	object->SetCameraAffected(false);
	
	_sprite = object->AddComponent<Sprite>();
	_transform = object->GetTransform();

	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("Mouse.png"));
	_sprite->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW + 1000);
	_sprite->SetOpacity(1);
	_transform->SetScale(Vector2(0.4f, 0.4f));
}

void Mouse::Update()
{
	Vector2 mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	Vector3 mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
	float mouseX = mousePosition_V3.x;
	float mouseY = (-1) * mousePosition_V3.y;

	_transform->SetPosition(Vector2(mouseX, mouseY - 2 ));
}