#include "stdafx.h"
#include "C3_StaffWindow.h"
#include "C3_Button.h"
#include <filesystem>
using namespace filesystem;

void C3_StaffWindow::Init()
{
	object->SetCameraAffected(false);

	object->AddComponent<BoxCollider>();

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/Category3Window.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);
	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(465, -777));

	for (auto d : directory_iterator("Resources/Sprite/UI/C3_Buttons/" + object->GetTag() + "Staff"))
	{
		_vButtonsForC3.push_back(d.path().string().substr(37 + object->GetTag().size()));
	}

	AddButtons();
}

void C3_StaffWindow::Update()
{

}

void C3_StaffWindow::OnMouseDown()
{

}

void C3_StaffWindow::AddButtons()
{
	for (int i = 0; i < _vButtonsForC3.size(); i++)
	{
		Object* button = Object::CreateObject(object);
		button->SetCameraAffected(false);
		button->AddComponent<Sprite>();
		button->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/C3_Buttons/Staff/" + _vButtonsForC3[i]));
		button->GetComponent<Sprite>()->SetDepth(10);
		if (i < 5)	button->GetTransform()->SetPosition(Vector2(-200 + i * 100, 30));
		else		button->GetTransform()->SetPosition(Vector2(-200 + (i % 5) * 100, -70));
		button->AddComponent<BoxCollider>();
		button->AddComponent<C3_Button>();
		button->SetName(_vButtonsForC3[i].substr(0, _vButtonsForC3[i].size() - 4));
		button->SetTag("Staff");
	}
}