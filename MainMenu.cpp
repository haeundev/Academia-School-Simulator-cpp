#include "stdafx.h"
#include "MainMenu.h"
#include "MapTool.h"
#include "Budget.h"
#include "GameScene.h"

void MainMenu::OnMouseDown()
{
	if (object->GetName() == "StartGame")
	{
		SceneManager::GetInstance()->PopScene();
		SceneManager::GetInstance()->PushScene(new GameScene);
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->SetIsSandBoxMode(false);
	}
	if (object->GetName() == "LoadGame")
	{
		SceneManager::GetInstance()->PopScene();
		SceneManager::GetInstance()->PushScene(new GameScene); 
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("MapTool")->GetComponent<MapTool>()->Load();
	}
	if (object->GetName() == "SandboxMode")
	{
		SceneManager::GetInstance()->PopScene();
		SceneManager::GetInstance()->PushScene(new GameScene); 
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->SetIsSandBoxMode(true);
	}
	if (object->GetName() == "QuitGame")
	{
		exit(0);
	}
}