#include "stdafx.h"
#include "RemoveButton.h"
#include "CharacterManager.h"

void RemoveButton::Init()
{
	_scene = SceneManager::GetInstance()->GetNowScene();
	_characterManager = _scene->GetChildByName("CharacterManager")->GetComponent<CharacterManager>();
}

void RemoveButton::OnMouseDown()
{
	_characterManager->FireFaculty(_nowFacultyName);

	Notify(MTYPE::FIRED, _nowFacultyName);
}