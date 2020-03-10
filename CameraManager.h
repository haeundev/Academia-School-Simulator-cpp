#pragma once
#include <vector>
#include <algorithm>
#include "Camera.h"

using namespace std;

class CameraManager
{
private:
	vector<Camera*> cameras;
	Camera* mainCamera;
	CameraManager();
public:
	static CameraManager* GetInstance();

	Camera* GetMainCamera() { return mainCamera; };
	Camera* GetRenderCamera();
	void AddCamera(Camera* camera);
	void SetMainCamera(Camera* camera) { mainCamera = camera; };
	vector<Camera*> GetCameras() { return cameras; };
	void SetIsActiveNowSceneCameras(bool _isActive);
	void DeleteCamera(Camera* _camera);
	void Update();
};

