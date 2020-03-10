#include "stdafx.h"
#include "ToDo.h"
#include "ToDoWindow.h"
#include "LinkButton.h"

void ToDo::Init()
{
	_todoWindow = Object::CreateObject();
	_todoWindow->AddComponent<ToDoWindow>();
	_todoWindow->SetIsActive(false);

	object->AddComponent<LinkButton>();
	object->GetComponent<LinkButton>()->SetLink(_todoWindow);

	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/Description/HotKeys.png"));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_descriptionBox->GetTransform()->SetPosition(Vector2(1370, -63));
	_descriptionBox->SetCameraAffected(false);
}

void ToDo::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0.85);
	}
	else
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
	}
}
