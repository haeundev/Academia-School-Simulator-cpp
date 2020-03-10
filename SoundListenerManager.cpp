#include "stdafx.h"
#include "GgaetIp.h"

SoundListenerManager::SoundListenerManager()
{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);

	FMOD_System_Set3DSettings(system, 10.0f, 10.0f, 10.0f);
	FMOD_System_GetMasterChannelGroup(system, &channelgroup);
	listener = CameraManager::GetInstance()->GetRenderCamera()->GetGameObject();
}

SoundListenerManager* SoundListenerManager::GetInstance()
{
	static SoundListenerManager* instance = new SoundListenerManager();
	return instance;
}

void SoundListenerManager::Update()
{
	if (listener == nullptr)
		return;
	if (isRenderCameraListener)
		listener = CameraManager::GetInstance()->GetRenderCamera()->GetGameObject();
	FMOD_VECTOR position,velocity,forward,up;
	Vector2 objPosition = listener->GetTransform()->GetWorldPosition();
	float rotation = listener->GetTransform()->GetRotation();
	position.x = objPosition.x /100;
	position.y = objPosition.y /100;
	position.z = 0;

	velocity.x = velocity.y = velocity.z = 0;

	forward.x = 0;
	forward.y = 0;
	forward.z = 1;

	Vector3 objUp = Vector3(0, 1, 0).Rotate(rotation,Vector3::forword);
	up.x = objUp.x ;
	up.y = objUp.y ;
	up.z = objUp.z;

	FMOD_System_Set3DListenerAttributes(system, 0, &position, &velocity, &forward, &up);
	FMOD_System_Update(system);
}