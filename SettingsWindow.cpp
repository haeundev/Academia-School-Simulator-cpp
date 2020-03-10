#include "stdafx.h"
#include "SettingsWindow.h"
#include "SettingsButton.h"
#include "ButtonPoly.h"
#include <filesystem>
using namespace filesystem;

void SettingsWindow::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("Management/Settings/BG.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);

	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(800, -450));

	object->AddComponent<BoxCollider>();

	_vButtonNames.push_back("QuitGame");
	_vButtonNames.push_back("AudioSetting");
	_vButtonNames.push_back("MainMenu");
	_vButtonNames.push_back("LoadMap");
	_vButtonNames.push_back("SaveMap");

	AddButtons();
}

void SettingsWindow::AddButtons()
{
	for (int i = 0; i < _vButtonNames.size(); i++)
	{
		Object* button = Object::CreateObject(object);
		button->SetCameraAffected(false);
		button->AddComponent<Sprite>();
		button->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Settings/Buttons/" + _vButtonNames[i] + ".png"));
		button->GetComponent<Sprite>()->SetDepth(10);
		button->GetTransform()->SetPosition(Vector2(0, -195 + 85 * i));
		button->AddComponent<BoxCollider>();
		button->AddComponent<SettingsButton>();
		button->SetName(_vButtonNames[i]);
		button->SetTag(object->GetTag());
		button->AddComponent<ButtonPoly>();
	}
}