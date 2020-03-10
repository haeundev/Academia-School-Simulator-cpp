#include "stdafx.h"
#include "ToDoDescriptionBox.h"

void ToDoDescriptionBox::Init()
{
	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/ToDo/Description/" + object->GetName()));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_descriptionBox->GetTransform()->SetPosition(Vector2(800, -630));
	_descriptionBox->SetCameraAffected(false);
	_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
}

void ToDoDescriptionBox::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0.85);
	}
	else
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
	}

	if (InputManager::GetInstance()->GetKeyDown('Q'))
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
	}
}