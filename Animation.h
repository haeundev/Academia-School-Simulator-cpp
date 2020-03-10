#pragma once
#include <string>
#include <d2d1.h>
#include <d2d1_1helper.h>

#pragma comment(lib,"d2d1.lib")

using namespace std;

class Vector2;
class Animation
{
private:
	shared_ptr<Image> image;
	Vector2 frameSize;
	Vector2 frameCount;
	float time = 1.f;
	bool repeat = false;
public:
	Animation();
	void SetImage(shared_ptr<Image> image);
	void SetFrameCount(Vector2 frameCount);
	void SetTime(float _time) { time = _time; };
	void SetRepeat(bool repeat) { this->repeat = repeat; };

	shared_ptr<Image> GetImage();
	Vector2 GetFrameSize();
	Vector2 GetFrameCount();
	float GetTimeManager() { return time; };
	bool GetRepeat() { return repeat; };
};