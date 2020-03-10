#pragma once
#include "GgaetIp.h"

class CharacterManager;
class C3_Button : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _c3Window;

	map<string, string> _mImagesForPlacing;
	string _clickedImageName;

	Scene* _scene;

	CharacterManager* _characterManager;

	Object* _costInfo;
	Object* _costInfoText;
	int _cost;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnMouseDown() override;
};