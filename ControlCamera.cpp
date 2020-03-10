#include "stdafx.h"
#include "ControlCamera.h"
#include <WinUser.h>

void ControlCamera::Init()
{
	transform = CameraManager::GetInstance()->GetRenderCamera()->GetTransform();
}

void ControlCamera::Update()
{
	Zoom();

	transform->SetScale(Vector2(_scale, _scale));

	if (InputManager::GetInstance()->GetKey('A'))
	{
		CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->Translate(Vector2(CameraMoveSpeed, 0));
	}
	if (InputManager::GetInstance()->GetKey('D'))
	{
		CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->Translate(Vector2(-CameraMoveSpeed, 0));
	}
	if (InputManager::GetInstance()->GetKey('W'))
	{
		CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->Translate(Vector2(0, -CameraMoveSpeed));
	}
	if (InputManager::GetInstance()->GetKey('S'))
	{
		CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->Translate(Vector2(0, CameraMoveSpeed));
	}
}

void ControlCamera::Zoom()
{
	if (!InputManager::GetInstance()->GetKey(VK_SHIFT)) return;

	if (!_zoomActive)
		return;

	_delta = InputManager::GetInstance()->GetWheelDelta();

	if (!_delta)
		return;
	if (_scale + _delta * _scaleSpeed < 0.03f ||
		_scale + _delta * _scaleSpeed > 1.3f)
		return;
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	_scale += _delta * _scaleSpeed;	
}