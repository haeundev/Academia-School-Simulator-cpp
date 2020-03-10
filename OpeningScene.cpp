#include "stdafx.h"
#include "OpeningScene.h"
#include "MainMenu.h"
#include "Mouse.h"
#include "ButtonPoly.h"

void OpeningScene::Init()
{
	Object* mainMenuBG = Object::CreateObject();
	mainMenuBG->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("OpeningSceneBG.png"));
	mainMenuBG->GetTransform()->SetPosition(Vector2(800, -450));
	mainMenuBG->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	mainMenuBG->SetCameraAffected(false);

	Object* mouse = Object::CreateObject();
	mouse->AddComponent<Mouse>();
	mouse->SetName("Mouse");
	mouse->SetCameraAffected(false);

	Object* startGameButton = Object::CreateObject();
	startGameButton->SetName("StartGame");
	startGameButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/MainMenu/StartGame.png"));
	startGameButton->AddComponent<BoxCollider>();
	startGameButton->AddComponent<MainMenu>();
	startGameButton->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(0, -86) + Vector2(800, -450));
	startGameButton->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	startGameButton->AddComponent<ButtonPoly>();
	startGameButton->SetCameraAffected(false);

	Object* loadGameButton = Object::CreateObject();
	loadGameButton->SetName("LoadGame");
	loadGameButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/MainMenu/LoadGame.png"));
	loadGameButton->AddComponent<BoxCollider>();
	loadGameButton->AddComponent<MainMenu>();
	loadGameButton->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(0, -220) + Vector2(800, -450));
	loadGameButton->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	loadGameButton->AddComponent<ButtonPoly>();
	loadGameButton->SetCameraAffected(false);

	Object* sandboxModeButton = Object::CreateObject();
	sandboxModeButton->SetName("SandboxMode");
	sandboxModeButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/MainMenu/SandboxMode.png"));
	sandboxModeButton->AddComponent<BoxCollider>();
	sandboxModeButton->AddComponent<MainMenu>();
	sandboxModeButton->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(0, -158) + Vector2(800, -450));
	sandboxModeButton->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	sandboxModeButton->AddComponent<ButtonPoly>();
	sandboxModeButton->SetCameraAffected(false);

	Object* quitGameButton = Object::CreateObject();
	quitGameButton->SetName("QuitGame");
	quitGameButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/MainMenu/QuitGame.png"));
	quitGameButton->AddComponent<BoxCollider>();
	quitGameButton->AddComponent<MainMenu>();
	quitGameButton->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(0, -282) + Vector2(800, -450));
	quitGameButton->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	quitGameButton->AddComponent<ButtonPoly>();
	quitGameButton->SetCameraAffected(false);
}