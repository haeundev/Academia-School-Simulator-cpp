#include "stdafx.h"
#include "AdmissionButton.h"
#include "AdmissionWindow.h"

void AdmissionButton::Init()
{
	object->AddComponent<BoxCollider>();
}

void AdmissionButton::Update()
{
	if (!InputManager::GetInstance()->GetKey(VK_LBUTTON)) return;

	if (!object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition())) return;

	count++;

	if (count > 3)
	{
		if (object->GetName() == "IncreaseButton")
		{
			object->GetParent()->GetComponent<AdmissionWindow>()->Increase();
		}
		if (object->GetName() == "DecreaseButton")
		{
			object->GetParent()->GetComponent<AdmissionWindow>()->Decrease();
		}

		count = 0;
	}
}