#pragma once
#include "GgaetIp.h"
#include <atlconv.h>
#include "Observed.h"

enum class PHASE
{
	BUILD_PHASE,
	PLAY_PHASE
};

class CharacterManager;
class TopBar : public Script, public Observed
{
private:
	float _realTime = 0.f;
	int _gameTime = 0;

	int count = 0;

	bool _doOnce = false;

	Text* _hourText; 
	Text* _minuteText;
	Text* _dayText;

	Text* _numOfFaculty;
	Text* _numOfStudents;
	Text* _numOfStaff;

	Object* _facultyNum; 
	Object* _studentsNum; 
	Object* _staffNum;

	Object* _hour; 
	Object* _minute; 
	Object* _day;

	Object* _zero;

	int _gameDayCount = 0;
	int _interval = 0;

	PHASE _phase = PHASE::BUILD_PHASE;

	CharacterManager* _characterManager;

	Object* _blackScreen;
	Object* _redScreen;
	float _blackOpacity = 0;
	float _redOpacity = 0;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetCMLink(CharacterManager* cm) { _characterManager = cm; }

	wstring String_to_wstring(string str)
	{
		USES_CONVERSION;
		return std::wstring(A2W(str.c_str()));
	}

	PHASE GetPhase() { return _phase; }
	void SetPhase(PHASE p) { _phase = p; }
	void AddGameDayCount() { _gameDayCount++; }
};