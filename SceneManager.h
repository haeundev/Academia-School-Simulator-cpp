#pragma once
#include <vector>

class Scene;
class SceneManager
{
private:
	vector<Scene*> scenes;
	SceneManager();
public:
	static SceneManager* GetInstance();

	void ReplaceScene(Scene* scene);
	void PushScene(Scene* scene);
	void PopScene();

	Scene* GetNowScene();
	vector<Scene*> GetScenes();
};

