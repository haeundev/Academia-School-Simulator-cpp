#pragma once
#include "GgaetIp.h"
#include "Observed.h"

class CharacterManager;
class RemoveButton : public Script, public Observed
{
private:
	Transform* _transform;
	Sprite* _sprite;

	map<string, int> _mFaculty;

	Scene* _scene;

	CharacterManager* _characterManager;

	string _nowFacultyName;

public:
	virtual void Init() override;
	virtual void OnMouseDown() override;

	void SetNowFacultyName(string s) { _nowFacultyName = s; }

};