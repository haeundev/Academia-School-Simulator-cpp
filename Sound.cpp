#include "stdafx.h"
#include "GgaetIp.h"

void Sound::Init()
{
	transform = object->GetTransform();
}

void Sound::Update()
{
	if (!audioClip)
		return;
	if (!audioClip->Get3D())
		return;

	Transform* listener = SoundListenerManager::GetInstance()->GetListner()->GetTransform();
	if ((listener->GetWorldPosition() - transform->GetWorldPosition()).Magnitude() >= audioClip->GetMaxDistance())
		FMOD_Channel_SetVolume(*audioClip->GetChannelPointer(), 0);
	else
		FMOD_Channel_SetVolume(*audioClip->GetChannelPointer(), audioClip->GetVolume());
	FMOD_VECTOR vel = { 0, 0.0f, 0.0f };
	FMOD_VECTOR position = { transform->GetWorldPosition().x /100,transform->GetWorldPosition().y /100,0 };
	FMOD_Channel_Set3DAttributes(*audioClip->GetChannelPointer(), &position, &vel, nullptr);
}

void Sound::Play()
{ 
	FMOD_CHANNEL** channel = audioClip->GetChannelPointer();
	FMOD_CHANNELGROUP* channelgroup = SoundListenerManager::GetInstance()->GetChannelGroup();
	FMOD_SYSTEM* system = SoundListenerManager::GetInstance()->GetSystem();
	if (audioClip->Get3D())
	{
		FMOD_VECTOR position = { transform->GetWorldPosition().x /100,transform->GetWorldPosition().y /100,0 };
		FMOD_VECTOR vel = { 0, 0.0f, 0.0f };
		FMOD_Channel_Set3DAttributes(*channel, &position, &vel, nullptr);
		FMOD_Channel_Set3DMinMaxDistance(*channel, audioClip->GetMinDistance(), 5000.f);
	}
	FMOD_System_PlaySound(system, audioClip->GetSound(), channelgroup, false, channel);
	FMOD_Channel_SetVolume(*channel, audioClip->GetVolume());
}

void Sound::Stop()
{
	FMOD_CHANNEL** channel = audioClip->GetChannelPointer();
	FMOD_Channel_Stop(*channel);
}

void Sound::Release()
{
	audioClip = nullptr;
	Component::Release();
}