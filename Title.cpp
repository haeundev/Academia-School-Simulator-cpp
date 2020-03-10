#include "stdafx.h"
#include "Title.h"
#include "GameScene.h"
#include "OpeningScene.h"

void Title::Init()
{
	ApplicationManager::GetInstance()->SetResolution(1600, 900, false);

	SceneManager::GetInstance()->PushScene(new GameScene);

	SceneManager::GetInstance()->PushScene(new OpeningScene);

	//ShowCursor(false);
}