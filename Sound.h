#pragma once
#include "Component.h"
#include "AudioClip.h"
#include "inc/fmod.h"
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"

#pragma comment(lib,"lib/fmod64_vc.lib")
#pragma comment(lib,"lib/fmodex64_vc.lib")
#pragma comment(lib,"lib/fmodexL64_vc.lib")

class Transform;
class Sound : public Component
{
private:
	Transform* transform;
	shared_ptr<AudioClip> audioClip;
public:
	void SetSound(shared_ptr<AudioClip> audioClip) { this->audioClip = audioClip; };
	shared_ptr<AudioClip> GetAudioClip() { return audioClip; };

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

	void Play();
	void Stop();
};

