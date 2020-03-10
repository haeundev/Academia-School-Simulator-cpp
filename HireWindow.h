#pragma once
#include "GgaetIp.h"
#include <stack>

class CharacterManager;
class HireWindow : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;
	Sprite* _infoSprite;

	vector<string>	_vFacultyNames;

	stack<string> _sNowFacultyname;

	CharacterManager* _characterManager;

	Object* _facultyButton;
	Object* _hireButton;
	Object* _removeButton;

public:
	virtual void Init() override;
	virtual void Update() override;

	void AddFacultyButtons();

	stack<string>& GetSNowFacultyName() { return _sNowFacultyname; }
};