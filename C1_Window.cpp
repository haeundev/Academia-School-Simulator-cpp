#include "stdafx.h"
#include "C1_Window.h"
#include "ControlCamera.h"
#include "C1_Button.h"
#include "C1_StaffButton.h"

void C1_Window::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/Category1Window.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);
	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(95, -777));

	for (int i = 0; i < 3; i++)
	{
		Object* button = Object::CreateObject(object);
		if (i == 0) button->SetName("Zones");
		if (i == 1) button->SetName("Build");
		if (i == 2) button->SetName("Objects");
		button->AddComponent<C1_Button>();
		button->GetTransform()->SetPosition(Vector2(0, 58 - i * 38));
		button->SetCameraAffected(false);
	}

	Object* staffButton = Object::CreateObject(object);
	staffButton->GetTransform()->SetPosition(Vector2(0, 58 - 3 * 38));
	staffButton->SetCameraAffected(false);
	staffButton->AddComponent<C1_StaffButton>();
	staffButton->SetName("Staff");
}

void C1_Window::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		_camera->GetComponent<ControlCamera>()->SetCanZoom(false);
	}
	else
	{
		_camera->GetComponent<ControlCamera>()->SetCanZoom(true);
	}

}