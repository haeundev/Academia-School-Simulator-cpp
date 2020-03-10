#include "stdafx.h"
#include "HireButton.h"
#include "CharacterManager.h"

void HireButton::Init()
{
	_scene = SceneManager::GetInstance()->GetNowScene();
	_characterManager = _scene->GetChildByName("CharacterManager")->GetComponent<CharacterManager>();
}

void HireButton::OnMouseDown()
{
	_characterManager->CreateFaculty(_nowFacultyName);

	Notify(MTYPE::HIRED, _nowFacultyName);
}