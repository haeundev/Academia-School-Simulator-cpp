#include "stdafx.h"
#include "GgaetIp.h"
#include "InputManager.h"

InputManager* InputManager::GetInstance()
{
	static InputManager* instance = new InputManager();
	return instance;
}

Vector2 InputManager::GetMousePosition()
{
	return mousePosition;
}

Vector2 InputManager::GetMouseWorldPosition()
{
	return mousePosition * (DesignResolution / ApplicationManager::GetInstance()->GetResolution());
}

void InputManager::SetMousePosition(Vector2 mousePosition)
{
	this->mousePosition = mousePosition;
}

bool InputManager::GetKey(int key)
{
	bool keyState = GetAsyncKeyState(key) & 0x8000;
	return keyState;
}

bool InputManager::GetKeyDown(int key)
{
	bool keyState = GetAsyncKeyState(key) & 0x8000;
	bool result = (keyState && keyStates[key] != KeyState::Down && keyStates[key] != KeyState::Stay) ? true : false;

	if (result)
		keyStates[key] = KeyState::Down;

	if (keyStates[key] == KeyState::Down)
		return true;
	return false;
}

bool InputManager::GetKeyUp(int key)
{
	bool keyState = GetAsyncKeyState(key) & 0x8000;
	bool result = (!keyState && (keyStates[key] == KeyState::Down || keyStates[key] == KeyState::Stay)) ? true : false;
	if (result)
		keyStates[key] = KeyState::Up;
	if (keyStates[key] == KeyState::Up)
		return true;
	return false;
}

void InputManager::Update()
{
	mouseWheelDelta = 0;
	for (auto k : keyStates)
	{
		bool keyState = GetAsyncKeyState(k.first) & 0x8000;
		switch (k.second)
		{
		case KeyState::Down:
			if (keyState)
				keyStates[k.first] = KeyState::Stay;
			else
				keyStates[k.first] = KeyState::Up;
			break;
		case KeyState::Stay:
			if (!keyState)
				keyStates[k.first] = KeyState::Up;
			break;
		case KeyState::Up:
			if (keyState)
				keyStates[k.first] = KeyState::Down;
			else
				keyStates[k.first] = KeyState::None;
			break;
		}
	}
}