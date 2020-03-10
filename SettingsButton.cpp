#include "stdafx.h"
#include "SettingsButton.h"
#include "OpeningScene.h"
#include "MapTool.h"

void SettingsButton::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()) 
		&& InputManager::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		if (object->GetName() == "SaveMap")
		{
			SceneManager::GetInstance()->GetNowScene()->GetChildByName("MapTool")->GetComponent<MapTool>()->Save();
		}
		if (object->GetName() == "LoadMap")
		{
			SceneManager::GetInstance()->GetNowScene()->GetChildByName("MapTool")->GetComponent<MapTool>()->Load();
		}
		if (object->GetName() == "MainMenu")
		{
			SceneManager::GetInstance()->PushScene(new OpeningScene);
		}
		if (object->GetName() == "AudioSetting")
		{

		}
		if (object->GetName() == "QuitGame")
		{
			exit(0);
		}

		_check = true;
	}
}