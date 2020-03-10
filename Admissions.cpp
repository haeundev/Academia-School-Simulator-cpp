#include "stdafx.h"
#include "Admissions.h"
#include "StartSchoolYear.h"
#include "AdmissionWindow.h"
#include "LinkButton.h"

void Admissions::Init()
{
	_admissionWindow = Object::CreateObject();
	_admissionWindow->AddComponent<AdmissionWindow>();
	_admissionWindow->SetIsActive(false);

	object->AddComponent<LinkButton>();
	object->GetComponent<LinkButton>()->SetLink(_admissionWindow);

	Object* startSchoolYear = Object::CreateObject();
	startSchoolYear->AddComponent<StartSchoolYear>();
	startSchoolYear->GetComponent<StartSchoolYear>()->SetTopBarLink(_topBar);
	startSchoolYear->SetCameraAffected(false);
	startSchoolYear->GetComponent<StartSchoolYear>()->SetAdmissionWindowLink(_admissionWindow->GetComponent<AdmissionWindow>());


	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/Description/Admissions.png"));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_descriptionBox->GetTransform()->SetPosition(Vector2(142, -125));
	_descriptionBox->SetCameraAffected(false);
}

void Admissions::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0.85);
	}
	else
	{
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
	}
}