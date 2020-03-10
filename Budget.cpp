#include "stdafx.h"
#include "Budget.h"
#include "BudgetNotification.h"

void Budget::Init()
{
	_budgetText = Object::CreateObject();
	_budgetText->AddComponent<Text>()->CreateText(to_wstring(_budgetValue), L"Times New Roman", L"ko-KR", { 1, 1, 0.3, 1 }, 24, 120, 80);
	_budgetText->SetCameraAffected(false);
	_budgetText->GetComponent<Text>()->GetTransform()->SetPosition(Vector2(520, -45));
	_budgetText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);

	if (_isSandBoxMode)
	{
		_budgetText->SetIsActive(false);
		object->SetIsActive(false);
	}
}

void Budget::Update()
{
	_budgetText->GetComponent<Text>()->ChangeText(to_wstring(_budgetValue));
}
