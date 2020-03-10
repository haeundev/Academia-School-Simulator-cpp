#include "stdafx.h"
#include "TopBar.h"
#include "CharacterManager.h"
#include "TimeTable.h"
#include "ToDo.h"
#include "Settings.h"
#include "Admissions.h"
#include "ButtonPoly.h"
#include "Budget.h"
#include "AdmissionWindow.h"

void TopBar::Init()
{
	Object* bar = Object::CreateObject();
	bar->SetCameraAffected(false);
	bar->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/Bar.png"));
	bar->GetTransform()->SetPosition(Vector2(800, -18));
	bar->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_WINDOW);

	Object* logo = Object::CreateObject();
	logo->SetCameraAffected(false);
	logo->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/SchoolLogo.png"));
	logo->GetTransform()->SetPosition(Vector2(800, -45));
	logo->GetComponent<Sprite>()->SetDepth((int)ZORDER::POLY_ON_UI);

	Object* toDo = Object::CreateObject();
	toDo->AddComponent<BoxCollider>();
	toDo->GetTransform()->SetPosition(Vector2(1500, -18));
	toDo->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TutorialButton.png"));
	toDo->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	toDo->AddComponent<ToDo>();
	toDo->AddComponent<ButtonPoly>();
	toDo->SetCameraAffected(false);

	Object* admissions = Object::CreateObject();
	admissions->AddComponent<BoxCollider>();
	admissions->GetTransform()->SetPosition(Vector2(100, -60));
	admissions->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/Admissions.png"));
	admissions->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_WINDOW);
	admissions->AddComponent<Admissions>();
	admissions->GetComponent<Admissions>()->SetTopBarLink(this);
	admissions->AddComponent<ButtonPoly>();
	admissions->SetCameraAffected(false);

	Object* settings = Object::CreateObject();
	settings->AddComponent<BoxCollider>();
	settings->GetTransform()->SetPosition(Vector2(1560, -18));
	settings->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/SettingsButton.png"));
	settings->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	settings->AddComponent<Settings>();
	settings->AddComponent<ButtonPoly>();
	settings->SetCameraAffected(false);

	// 날짜, 시간 표시 관련
	_day = Object::CreateObject();
	_day->GetTransform()->SetPosition(Vector2(1125, -45));
	_dayText = _day->AddComponent<Text>();
	_dayText->CreateText(to_wstring(_gameDayCount), L"Times New Roman", L"ko-KR", { 1,1,1,0.9f }, 24, 40, 80);
	_dayText->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_day->SetCameraAffected(false);

	_hour = Object::CreateObject();
	_hour->GetTransform()->SetPosition(Vector2(1090 + 90, -45));
	_hourText = _hour->AddComponent<Text>();
	_hourText->CreateText(to_wstring(_gameTime / 3600), L"Times New Roman", L"ko-KR", { 1,1,1,1 }, 24, 40, 80);
	_hourText->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_hour->SetCameraAffected(false);

	_zero = Object::CreateObject();
	_zero->GetTransform()->SetPosition(Vector2(1135 + 90, -45));
	_zero->AddComponent<Text>();
	_zero->GetComponent<Text>()->CreateText(to_wstring(0), L"Times New Roman", L"ko-KR", { 1,1,1,1 }, 24, 40, 80);
	_zero->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_zero->SetCameraAffected(false);

	_minute = Object::CreateObject();
	_minute->GetTransform()->SetPosition(Vector2(1145 + 90, -45));
	_minuteText = _minute->AddComponent<Text>();
	_minuteText->CreateText(to_wstring(_gameTime / 60), L"Times New Roman", L"ko-KR", { 1,1,1,1 }, 24, 40, 80);
	_minuteText->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_minute->SetCameraAffected(false);


	// 교사, 직원, 학생 수 관련
	_facultyNum = Object::CreateObject();
	_facultyNum->GetTransform()->SetPosition(Vector2(70, -45));
	_numOfFaculty = _facultyNum->AddComponent<Text>();
	_numOfFaculty->CreateText(to_wstring(_characterManager->GetFacultyNum()), L"Times New Roman", L"ko-KR", { 1,1,1,1 }, 24, 40, 80);
	_numOfFaculty->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_facultyNum->SetCameraAffected(false);

	_staffNum = Object::CreateObject();
	_staffNum->GetTransform()->SetPosition(Vector2(160, -45));
	_numOfStaff = _staffNum->AddComponent<Text>();
	_numOfStaff->CreateText(to_wstring(_characterManager->GetVStaff().size()), L"Times New Roman", L"ko-KR", { 1,1,1,1 }, 24, 40, 80);
	_numOfStaff->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_staffNum->SetCameraAffected(false);

	_studentsNum = Object::CreateObject();
	_studentsNum->GetTransform()->SetPosition(Vector2(249, -45));
	_numOfStudents = _studentsNum->AddComponent<Text>();
	_numOfStudents->CreateText(to_wstring(_characterManager->GetVStudents().size()), L"Times New Roman", L"ko-KR", { 1,1,1,1 }, 24, 40, 80);
	_numOfStudents->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
	_studentsNum->SetCameraAffected(false);

	_realTime = 0;

	_blackScreen = Object::CreateObject();
	_blackScreen->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("BlackScreen.png"));
	_blackScreen->GetComponent<Sprite>()->SetDepth((int)ZORDER::SCREEN);
	_blackScreen->GetComponent<Sprite>()->SetOpacity(_blackOpacity);
	_blackScreen->GetTransform()->SetPosition(Vector2(800, -450));
	_blackScreen->SetCameraAffected(false);

	_redScreen = Object::CreateObject();
	_redScreen->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("RedScreen.png"));
	_redScreen->GetComponent<Sprite>()->SetDepth((int)ZORDER::LAND);
	_redScreen->GetComponent<Sprite>()->SetOpacity(_redOpacity);
	_redScreen->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + GridWidth * TotalGridX / 2 - GridWidth / 2,
		GRID_STARTPOINT.y - GridHeight * TotalGridY / 2 + GridHeight / 2));
}

void TopBar::Update()
{
	if ((_gameTime / 60) % 60 < 10)
	{
		_minute->GetTransform()->SetPosition(Vector2(1135 + 12 + 90, -45));
		_zero->SetIsActive(true);
	}
	else
	{
		_minute->GetTransform()->SetPosition(Vector2(1135 + 90, -45));
		_zero->SetIsActive(false);
	}
	_gameTime = (int)(_realTime * 48 + 21600);
	_hourText->ChangeText(to_wstring(_gameTime / 3600 % 12 + 1));
	_minuteText->ChangeText(to_wstring((_gameTime / 60) % 60));
	_dayText->ChangeText(to_wstring(_gameDayCount));

	_blackScreen->GetComponent<Sprite>()->SetOpacity(_blackOpacity);


	if (_phase == PHASE::BUILD_PHASE)
	{
		_interval++;

		_redOpacity = 0.f;

		if (_blackOpacity > 0 && _gameDayCount > 1 && _interval > 20)
			_blackOpacity -= 0.015f;
	}
	else if (_phase == PHASE::PLAY_PHASE)
	{
		// 시계 업데이트
		_realTime += /*0.02f*/ 0.07f;

		_redScreen->GetComponent<Sprite>()->SetOpacity(_redOpacity);

		// 시간표에 따라 Notify
		if (_gameTime / 3600 % 12 + 1 == 7 && (_gameTime / 60) % 60 == 3)
		{
			Notify(MTYPE::TIME, "NewDay");

			if (!_doOnce)
				Notify(MTYPE::TIME, "Homeroom_StaffIn");
			_doOnce = true;

		}
		else if (_gameTime / 3600 % 12 + 1 == 8)
		{
			if (_doOnce)
				Notify(MTYPE::TIME, "Homeroom_StudentsIn");
			_doOnce = false;
		}
		else if (_gameTime / 3600 % 12 + 1 == 9)
		{
			if (!_doOnce)
				Notify(MTYPE::TIME, "FirstPeriod");
			_doOnce = true;
		}
		else if (_gameTime / 3600 % 12 + 1 == 10)
		{
			if (_doOnce)
				Notify(MTYPE::TIME, "SecondPeriod");
			_doOnce = false;
		}
		else if (_gameTime / 3600 % 12 + 1 == 11)
		{
			if (!_doOnce)
				Notify(MTYPE::TIME, "ThirdPeriod");
			_doOnce = true;
		}
		else if (_gameTime / 3600 % 12 + 1 == 12)
		{
			if (_doOnce)
				Notify(MTYPE::TIME, "FourthPeriod");
			_doOnce = false;
		}
		else if (_gameTime / 3600 % 12 + 1 == 1)
		{
			if (!_doOnce)
				Notify(MTYPE::TIME, "FifthPeriod");
			_doOnce = true;
		}
		else if (_gameTime / 3600 % 12 + 1 == 2)
		{
			if (_doOnce)
				Notify(MTYPE::TIME, "SixthPeriod");
			_doOnce = false;
		}
		else if (_gameTime / 3600 % 12 + 1 == 3)
		{
			if (!_doOnce)
				Notify(MTYPE::TIME, "SeventhPeriod");
			_doOnce = true;
		}
		else if (_gameTime / 3600 % 12 + 1 == 4)
		{
			if (_redOpacity < 1.f) _redOpacity += 0.02f;

			if (_doOnce)
				Notify(MTYPE::TIME, "EighthPeriod");
			_doOnce = false;
		}
		else if (_gameTime / 3600 % 12 + 1 == 5)
		{
			if (!_doOnce)
				Notify(MTYPE::TIME, "Dismissal_AllOut");
			_doOnce = true;
		}

		// 밝아지는 조건
		if (_gameTime / 3600 % 12 + 1 == 7 && (_gameTime / 60) % 60 > 1)
		{
			if (_blackOpacity > 0)	_blackOpacity -= 0.015f;
		}
		// 어두워지는 조건
		else if (_gameTime / 3600 % 12 + 1 == 5 && (_gameTime / 60) % 60 > 30)
		{
			if (_blackOpacity < 1)	_blackOpacity += 0.015f;
		}

		// 하루 재시작
		if (_blackOpacity >= 1.f)
		{
			_realTime = 0;

			_interval = 0;

			_redOpacity = 0.f;

			_phase = PHASE::BUILD_PHASE;
		}
	}

	// 인원 표시 업데이트
	_numOfFaculty->ChangeText(to_wstring(_characterManager->GetFacultyNum()));
	_numOfStaff->ChangeText(to_wstring(_characterManager->GetVStaff().size()));
	_numOfStudents->ChangeText(to_wstring(_characterManager->GetVStudents().size()));
}