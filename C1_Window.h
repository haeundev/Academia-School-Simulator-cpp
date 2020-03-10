#pragma once
#include "GgaetIp.h"

class ControlCamera;
class C1_Window : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _camera;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetCameraLink(Object* c) { _camera = c; }
	Object* GetCamera() { return _camera; }
};