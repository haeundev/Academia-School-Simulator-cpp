#include "stdafx.h"
#include "GgaetIp.h"

void Camera::Awake()
{
	transform = object->GetTransform();
	CameraManager::GetInstance()->AddCamera(this);
}

void Camera::Release()
{
	CameraManager::GetInstance()->DeleteCamera(this);
	Component::Release();
}