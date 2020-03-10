#include "stdafx.h"
#include "GgaetIp.h"
#include "AudioClip.h"

shared_ptr<AudioClip> AudioClip::CreateSound(string path, bool is3D)
{
	FMOD_SOUND* sound;

	string path1 = "Resources/Sound/" + path;

	if (is3D)
		FMOD_System_CreateSound(SoundListenerManager::GetInstance()->GetSystem(), path1.c_str(), FMOD_3D, NULL, &sound);
	else
		FMOD_System_CreateStream(SoundListenerManager::GetInstance()->GetSystem(), path1.c_str(), FMOD_NONBLOCKING, NULL, &sound);
	auto newSound = shared_ptr<AudioClip>(new AudioClip(sound, is3D));
	return newSound;
}

AudioClip::AudioClip(FMOD_SOUND* sound, bool is3D)
{
	this->sound = sound;
	this->is3D = is3D;
}


void AudioClip::Release()
{
	FMOD_Sound_Release(sound);
}