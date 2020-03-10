#include "stdafx.h"
#include "LinkButton.h"

void LinkButton::Init()
{
	object->AddComponent<BoxCollider>();
}

void LinkButton::Update()
{
	if (linked->GetIsActive() 
		&& InputManager::GetInstance()->GetKeyDown('Q') )
	{
		linked->SetIsActive(false);
	}
}

void LinkButton::OnMouseDown()
{
	linked->SetIsActive(!linked->GetIsActive());
}