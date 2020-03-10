#include "stdafx.h"
#include "Guideline.h"

void Guideline::Update()
{
	if (object->GetName() == "Guideline")
	{
		if (InputManager::GetInstance()->GetKeyDown(VK_F1))
		{
			object->GetComponent<Sprite>()->SetOpacity(0.85);
		}
		if (InputManager::GetInstance()->GetKeyDown(VK_F2))
		{
			object->GetComponent<Sprite>()->SetOpacity(0);
		}
	}
	if (object->GetName() == "GuideFloor")
	{
		if (InputManager::GetInstance()->GetKeyDown(VK_F3))
		{
			object->GetComponent<Sprite>()->SetOpacity(1);
		}
		if (InputManager::GetInstance()->GetKeyDown(VK_F4))
		{
			object->GetComponent<Sprite>()->SetOpacity(0);
		}
	}
}
