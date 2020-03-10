#include "stdafx.h"
#include "ToDoWindow.h"
#include "ButtonPoly.h"
#include "ToDoDescriptionBox.h"

#include <filesystem>
using namespace filesystem;

void ToDoWindow::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("Management/ToDo/BG.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);

	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(800, -450));

	object->AddComponent<BoxCollider>();

	AddList();
}

void ToDoWindow::AddList()
{
	int i = 0;

	for (auto d : directory_iterator("Resources/Sprite/Management/ToDo/Before"))
	{
		Object* box = Object::CreateObject(object);
		box->SetCameraAffected(false);
		box->SetName(d.path().string().substr(40));
		box->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()
			->AddImage("Management/ToDo/Before/" + box->GetName()));
		box->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
		box->AddComponent<BoxCollider>();
		box->AddComponent<ButtonPoly>();
		box->GetTransform()->SetPosition(Vector2(0, 155 - 34.2 * i));
		box->AddComponent<ToDoDescriptionBox>();

		i++;
	}
}