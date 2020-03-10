#include "stdafx.h"
#include "BudgetNotification.h"

void BudgetNotification::Init()
{
	object->AddComponent<Text>();
	_text = object->GetComponent<Text>();
	_text->CreateText(L"0", L"Times New Roman", L"ko-KR", { 1, 1, 1, 0 }, 24, 200, 80);
	_text->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	object->GetTransform()->SetPosition(Vector2(650, -45));
	object->SetCameraAffected(false);
}

void BudgetNotification::Update()
{
	if (!_notified) return;

	_count++;

	_opacity -= 0.02f;

	if (_count > 10)
	{
		_count = 0;
	}

	_text->SetColor({ 1.f, 0.f, 0.f, _opacity }, 0, 4);
	
	if (_opacity <= 0)
	{
		_notified = false;
	}
}

void BudgetNotification::OnNotify(MTYPE type, string event)
{
	_notified = true;
	_type = type;
	_event = event;

	_opacity = 1.f;

	if (_type == MTYPE::BUDGET_MINUS)
	{
		_text->ChangeText(String_to_wstring(_event));
		_text->SetColor({ 1.f, 0.f, 0.f, _opacity }, 0, _event.length() + 1);
	}
	if (_type == MTYPE::BUDGET_PLUS)
	{
		_text->ChangeText(String_to_wstring("+ " + _event));
		_text->SetColor({ 0.f, 1.f, 0.f, _opacity }, 0, _event.length() + 1);
	}
}