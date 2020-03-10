#include "stdafx.h"
#include "Settings.h"
#include "ButtonPoly.h"
#include "LinkButton.h"
#include "SettingsWindow.h"

void Settings::Init()
{
	_settingsWindow = Object::CreateObject();
	_settingsWindow->AddComponent<SettingsWindow>();
	_settingsWindow->SetIsActive(false);

	object->AddComponent<LinkButton>();
	object->GetComponent<LinkButton>()->SetLink(_settingsWindow);

	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/Description/Settings.png"));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_descriptionBox->GetTransform()->SetPosition(Vector2(1400, -63));
	_descriptionBox->SetCameraAffected(false);
}

void Settings::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(VK_ESCAPE))
	{
		_settingsWindow->SetIsActive(!_settingsWindow->GetIsActive());
	}

	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0.85);
	}
	else
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
	}
}