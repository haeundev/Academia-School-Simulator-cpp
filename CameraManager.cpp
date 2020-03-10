#include "stdafx.h"
#include "GgaetIp.h"

CameraManager::CameraManager() {}

CameraManager* CameraManager::GetInstance()
{
	static CameraManager* instance = new CameraManager();
	return instance;
}

Camera* CameraManager::GetRenderCamera()
{
	cameras[0]->GetTransform()->Update();
	return cameras[0];
}

bool Compare(Camera* a, Camera* b)
{
	return a->GetDepth() > b->GetDepth() ? a->GetGameObject()->GetIsActive() ? true : false : false;
}

void CameraManager::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
	sort(cameras.begin(), cameras.end(), Compare);
}

void CameraManager::Update()
{
	sort(cameras.begin(), cameras.end(), Compare);
}

void CameraManager::DeleteCamera(Camera* _camera)
{
	for (auto itr = cameras.begin(); itr < cameras.end(); itr++)
	{
		if (*itr != _camera)
			continue;

		cameras.erase(itr);
		return;
	}
}

void CameraManager::SetIsActiveNowSceneCameras(bool _isActive)
{
	for (Camera* c : cameras)
		c->GetGameObject()->SetIsActive(_isActive);
}