#pragma once
#include "inc/fmod.h"
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"
#include <memory>

#pragma comment(lib,"lib/fmod64_vc.lib")
#pragma comment(lib,"lib/fmodex64_vc.lib")
#pragma comment(lib,"lib/fmodexL64_vc.lib")

class AudioClip
{
private:
	FMOD_SOUND* sound;
	FMOD_CHANNEL* channel;
	FMOD_SYSTEM* system;

	float volume = 1.f;

	int maxDistance = 600;
	int minDistance = 150;

	bool is3D = false;

	AudioClip() {};
	AudioClip(FMOD_SOUND* sound, bool is3D);
public:
	static shared_ptr<AudioClip> CreateSound(string path, bool is3D = false);

	void SetVolume(float volume) { this->volume = volume; };
	void SetMaxDistance(int maxDistance) { this->maxDistance = maxDistance; };
	void SetMinDistance(int minDistance) { this->minDistance = minDistance; };
	void Set3D(bool is3D) { this->is3D = is3D; };

	int GetMaxDistance() { return maxDistance; };
	int GetMinDistance() { return minDistance; };
	float GetVolume() { return volume; };
	bool Get3D() { return is3D; };

	FMOD_SOUND* GetSound() { return sound; };
	FMOD_CHANNEL** GetChannelPointer() { return &channel; };

	void Release();
};

