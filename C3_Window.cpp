#include "stdafx.h"
#include "C3_Button.h"
#include "C3_Window.h"

#include <filesystem>
using namespace filesystem;

void C3_Window::Init()
{
	object->SetCameraAffected(false);

	object->AddComponent<BoxCollider>();

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/Category3Window.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);
	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(723, -790));

	for (auto d : directory_iterator("Resources/Sprite/UI/C3_Buttons/" + object->GetTag() /*Zone, Build, Objects*/
		+ "/" + object->GetName() /*Admin, ArtRoom, AVRoom,...*/))
	{
		_vButtonsForC3.push_back(d.path().string().substr(33 + object->GetTag().size() + object->GetName().size()));
	}

	AddButtons();
}

void C3_Window::Update()
{
	if (object->GetIsActive()
		&& InputManager::GetInstance()->GetKeyDown('Q'))
	{
		object->SetIsActive(false);
	}
}

void C3_Window::AddButtons()
{
	for (int i = 0; i < _vButtonsForC3.size(); i++)
	{
		Object* button = Object::CreateObject(object);
		button->SetCameraAffected(false);
		button->AddComponent<Sprite>();
		button->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/C3_Buttons/" + object->GetTag() + "/" +
			object->GetName() + "/" + _vButtonsForC3[i]));
		button->GetComponent<Sprite>()->SetDepth(10);
		button->GetTransform()->SetPosition(Vector2(-200 + i * 98, 30));
		button->AddComponent<BoxCollider>();
		button->AddComponent<C3_Button>();
		button->SetName(_vButtonsForC3[i].substr(0, _vButtonsForC3[i].size() - 4));
		button->SetTag(object->GetTag());
	}
}