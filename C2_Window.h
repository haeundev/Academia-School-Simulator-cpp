#pragma once
#include "GgaetIp.h"

class ControlCamera;
class C2_Window : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	vector<string>	_vButtonsForC2;

	string _C2WindowTag;

	Object* _camera;
	Object* _c1Window;

	float _delta;
	float _scrollSpeed = 18.f;

	Vector2 mousePosition;
	Vector3 mousePosition_V3;
	Vector3 mouseWorldPosition;
	float mouseX;
	float mouseY;

	Vector2 _currentIndex;


public:
	virtual void Init() override;
	virtual void Update() override;

	void StopZoomAndJustScroll();
	void SetC2WindowTag(string s) { _C2WindowTag = s; }
	void AddButtons();

	void SetCameraLink(Object* c) { _camera = c; }
	void SetC1WindowLink(Object* c) { _c1Window = c; }
};