#pragma once
class TimeManager
{
private:
	float startTime;
	float deltaTime = 0;
	TimeManager();
public:
	static TimeManager* GetInstance();
	float GetTime();
	float GetDeltaTime();

	void SetDeltaTime(float _deltaTime);
};

