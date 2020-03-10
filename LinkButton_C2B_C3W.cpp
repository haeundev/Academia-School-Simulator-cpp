#include "stdafx.h"
#include "LinkButton_C2B_C3W.h"

void LinkButton_C2B_C3W::Init()
{
	object->AddComponent<BoxCollider>();
}

void LinkButton_C2B_C3W::Update()
{
	if (linked->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->SetIsActive(true);
	}
	//else if (linked->GetIsActive()
	//	&& InputManager::GetInstance()->GetKeyDown(VK_LBUTTON)
	//	&& !linked->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition())
	//	&& !object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	//{
	//	linked->SetIsActive(false);
	//}

	if (linked->GetIsActive()
		&& InputManager::GetInstance()->GetKeyDown('Q'))
	{
		linked->SetIsActive(false);
	}
}

void LinkButton_C2B_C3W::OnMouseDown()
{
	linked->SetIsActive(!linked->GetIsActive());
}
