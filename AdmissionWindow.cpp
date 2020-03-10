#include "stdafx.h"
#include "AdmissionWindow.h"
#include "AdmissionButton.h"
#include "ButtonPoly.h"
#include "Budget.h"
#include "TopBar.h"

void AdmissionWindow::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("Management/Admissions/BG.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);

	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(800, -450));

	object->AddComponent<BoxCollider>();

	_interested = 13 - _incoming;
	_incoming = 13 - _interested;
	_returning = 11;
	_total = _incoming + _returning;
	_tuition = _total * 90;
	_subsidy = _total * 45;

	_interestedText = Object::CreateObject(object);
	_interestedText->AddComponent<Text>()->CreateText(to_wstring(_interested), L"Times New Roman", L"ko-KR", { 1, 1, 1, 1 }, 24, 120, 80);
	_interestedText->SetCameraAffected(false);
	_interestedText->GetComponent<Text>()->GetTransform()->SetPosition(Vector2(-222, -63));
	_interestedText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);

	_incomingText = Object::CreateObject(object);
	_incomingText->AddComponent<Text>()->CreateText(to_wstring(_incoming), L"Times New Roman", L"ko-KR", { 1, 1, 1, 1 }, 24, 120, 80);
	_incomingText->SetCameraAffected(false);
	_incomingText->GetComponent<Text>()->GetTransform()->SetPosition(Vector2(-115, -63));
	_incomingText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);

	_returningText = Object::CreateObject(object);
	_returningText->AddComponent<Text>()->CreateText(to_wstring(_returning), L"Times New Roman", L"ko-KR", { 1, 1, 1, 1 }, 24, 120, 80);
	_returningText->SetCameraAffected(false);
	_returningText->GetComponent<Text>()->GetTransform()->SetPosition(Vector2(-15, -63));
	_returningText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);

	_totalText = Object::CreateObject(object);
	_totalText->AddComponent<Text>()->CreateText(to_wstring(_total), L"Times New Roman", L"ko-KR", { 1, 1, 1, 1 }, 24, 120, 80);
	_totalText->SetCameraAffected(false);
	_totalText->GetComponent<Text>()->GetTransform()->SetPosition(Vector2(85, -63));
	_totalText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);

	_tuitionText = Object::CreateObject(object);
	_tuitionText->AddComponent<Text>()->CreateText(to_wstring(_tuition), L"Times New Roman", L"ko-KR", { 1, 1, 1, 1 }, 24, 120, 80);
	_tuitionText->SetCameraAffected(false);
	_tuitionText->GetComponent<Text>()->GetTransform()->SetPosition(Vector2(178, -63));
	_tuitionText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);

	_subsidyText = Object::CreateObject(object);
	_subsidyText->AddComponent<Text>()->CreateText(to_wstring(_subsidy), L"Times New Roman", L"ko-KR", { 1, 1, 1, 1 }, 24, 120, 80);
	_subsidyText->SetCameraAffected(false);
	_subsidyText->GetComponent<Text>()->GetTransform()->SetPosition(Vector2(275, -63));
	_subsidyText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);

	_increaseButton = Object::CreateObject(object);
	_increaseButton->SetName("IncreaseButton");
	_increaseButton->SetCameraAffected(false);
	_increaseButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Admissions/IncreaseButton.png"));
	_increaseButton->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_increaseButton->GetTransform()->SetPosition(Vector2(-135, -37));
	_increaseButton->AddComponent<AdmissionButton>();

	_decreaseButton = Object::CreateObject(object);
	_decreaseButton->SetName("DecreaseButton");
	_decreaseButton->SetCameraAffected(false);
	_decreaseButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Admissions/DecreaseButton.png"));
	_decreaseButton->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_decreaseButton->GetTransform()->SetPosition(Vector2(-204, -37));
	_decreaseButton->AddComponent<AdmissionButton>();

	_greenStartButton = Object::CreateObject();
	_greenStartButton->AddComponent<BoxCollider>();
	_greenStartButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/StartSchoolYear_Green.png"));
	_greenStartButton->AddComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_greenStartButton->AddComponent<ButtonPoly>();
	_greenStartButton->GetTransform()->SetPosition(Vector2(300, -60));
	_greenStartButton->SetIsActive(false);
	_greenStartButton->SetCameraAffected(false);

	SceneManager::GetInstance()->GetNowScene()->GetChildByName("TopBar")->GetComponent<TopBar>()->AddObserver(this);
}

void AdmissionWindow::Update()
{
	_interested = 13 - _incoming;
	_incoming = 13 - _interested;
	_tuition = _total * 90;
	_subsidy = _total * 45;
	_total = _incoming + _returning;

	_interestedText->GetComponent<Text>()->ChangeText(to_wstring(_interested));
	_incomingText->GetComponent<Text>()->ChangeText(to_wstring(_incoming));
	_returningText->GetComponent<Text>()->ChangeText(to_wstring(_returning));
	_totalText->GetComponent<Text>()->ChangeText(to_wstring(_total));
	_tuitionText->GetComponent<Text>()->ChangeText(to_wstring(_tuition));
	_subsidyText->GetComponent<Text>()->ChangeText(to_wstring(_subsidy));

	if (_total >= 20 && !_greenStartButton->GetIsActive())
	{
		_greenStartButton->SetIsActive(true);
	}
	else if (_total < 20 && _greenStartButton->GetIsActive())
	{
		_greenStartButton->SetIsActive(false);
	}
}

void AdmissionWindow::OnNotify(MTYPE type, string event)
{
	if (type != MTYPE::TIME || event != "NewDay") return;

	SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->BudgetPlus(_tuition + _subsidy);
}