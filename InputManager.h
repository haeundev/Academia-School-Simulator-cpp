#pragma once
#include <map>

using namespace std;

enum class KeyState
{
	None,
	Down,
	Stay,
	Up
};

class InputManager
{
private:
	map<int, KeyState> keyStates;
	Vector2 mousePosition;
	float mouseWheelDelta = 0;
public:
	static InputManager* GetInstance();

	void SetMousePosition(Vector2 mousePosition);

	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	float GetWheelDelta() { return mouseWheelDelta; }
	void SetWheelDelta(float wheelDelta) { mouseWheelDelta = wheelDelta; }

	void Update();

	Vector2 GetMousePosition();
	Vector2 GetMouseWorldPosition();


};

