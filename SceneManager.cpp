#include "stdafx.h"
#include "SceneManager.h"
#include "GgaetIp.h"
#include "Title.h"

SceneManager::SceneManager()
{
	scenes.push_back(new Title());
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager* instance = new SceneManager();
	return instance;
}

vector<Scene*> SceneManager::GetScenes()
{
	return scenes;
}

void SceneManager::ReplaceScene(Scene* scene)
{
	for (Scene* s : scenes)
		s->Release();
	scenes.clear();

	scenes.push_back(scene);
	scene->RunSceneInit();
	PhysicsManager::GetInstance()->SetWorld(scene->GetWorld());
	scene->Init();
}

void SceneManager::PushScene(Scene* scene)
{
	CameraManager::GetInstance()->SetIsActiveNowSceneCameras(false);
	scenes.push_back(scene);
	scene->RunSceneInit();
	PhysicsManager::GetInstance()->SetWorld(scene->GetWorld());
	scene->Init();
	for (Object* c : scene->GetChildren())
		c->Init();
}

void SceneManager::PopScene()
{
	scenes[scenes.size() - 1]->Release();
	scenes.pop_back();
	CameraManager::GetInstance()->SetMainCamera(scenes[scenes.size() - 1]->GetMainCamera());
	CameraManager::GetInstance()->SetIsActiveNowSceneCameras(true);
	PhysicsManager::GetInstance()->SetWorld(scenes[scenes.size() - 1]->GetWorld());
}

Scene* SceneManager::GetNowScene()
{
	return scenes[scenes.size() - 1];
}