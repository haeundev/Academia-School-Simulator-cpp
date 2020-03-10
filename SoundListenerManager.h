#pragma once
#include "inc/fmod.h"
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"

#pragma comment(lib,"lib/fmod64_vc.lib")
#pragma comment(lib,"lib/fmodex64_vc.lib")
#pragma comment(lib,"lib/fmodexL64_vc.lib")

class Transform;
class Object;

class SoundListenerManager
{
private:
	FMOD_SYSTEM* system;
	FMOD_CHANNELGROUP* channelgroup;
	Object* listener;

	bool isRenderCameraListener = true;

	SoundListenerManager();
public:
	static SoundListenerManager* GetInstance();
	FMOD_SYSTEM* GetSystem() { return system; };
	FMOD_CHANNELGROUP* GetChannelGroup() { return channelgroup; };

	void SetListner(Object* listner) { this->listener = listner; };
	Object* GetListner() { return listener; };

	void SetIsRenderCameraListener(bool isRenderCameraListener) { this->isRenderCameraListener = isRenderCameraListener; };
	bool GetIsRenderCameraListener() { return isRenderCameraListener; };

	void Update();
};

