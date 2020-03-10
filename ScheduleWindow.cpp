#include "stdafx.h"
#include "ScheduleWindow.h"
#include "ChangeSchedule.h"

void ScheduleWindow::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("Schedule/BG.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);

	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(800, -450));

	object->AddComponent<BoxCollider>();

	_vPeriods.push_back("Language");
	_vPeriods.push_back("Math");
	_vPeriods.push_back("Recess");
	_vPeriods.push_back("Science");
	_vPeriods.push_back("History");
	_vPeriods.push_back("Art");
	_vPeriods.push_back("Lunch");
	_vPeriods.push_back("PE");
	_vPeriods.push_back("Dismissal");

	_vPosPerPeriod_Student.push_back({ Vector2(14, 8), Vector2(14, 9) });		   // Language
	_vPosPerPeriod_Student.push_back({ Vector2(41, 8), Vector2(41, 9) });		   // Math
	_vPosPerPeriod_Student.push_back({ Vector2(24, 19), Vector2(32, 19) });		   // Recess
	_vPosPerPeriod_Student.push_back({ Vector2(16, 19), Vector2(16, 20) });		   // Science
	_vPosPerPeriod_Student.push_back({ Vector2(41, 30), Vector2(41, 31) });		   // History
	_vPosPerPeriod_Student.push_back({ Vector2(7, 7), Vector2(7, 9) });			   // Art
	_vPosPerPeriod_Student.push_back({ Vector2(7, 19), Vector2(10, 20) });		   // Lunch
	_vPosPerPeriod_Student.push_back({ Vector2(32, 37), Vector2(39, 37) });		   // PE
	_vPosPerPeriod_Student.push_back({ Vector2(49, 49), Vector2(49, 48) });		   // Dismissal

	SetButtons();
}

void ScheduleWindow::OnNotify(MTYPE mtype, string event)
{
	if (mtype == MTYPE::SCHEDULE_UP)
	{
		for (int i = 0; i < _vOrder.size(); i++)
		{
			if (_vOrder[i]->GetName() == event)
			{
				if (i == 0) return;
				
				Object* temp = _vOrder[i];
				_vOrder[i] = _vOrder[i - 1];
				_vOrder[i - 1] = temp;

				vector<Vector2> temp2 = _vPosPerPeriod_Student[i];
				_vPosPerPeriod_Student[i] = _vPosPerPeriod_Student[i - 1];
				_vPosPerPeriod_Student[i - 1] = temp2;

				break;
			}
		}
	}

	if (mtype == MTYPE::SCHEDULE_DOWN)
	{
		for (int i = 0; i < _vOrder.size(); i++)
		{
			if (_vOrder[i]->GetName() == event)
			{
				if (i == _vOrder.size() - 1) return;

				Object* temp = _vOrder[i];
				_vOrder[i] = _vOrder[i + 1];
				_vOrder[i + 1] = temp;

				vector<Vector2> temp2 = _vPosPerPeriod_Student[i];
				_vPosPerPeriod_Student[i] = _vPosPerPeriod_Student[i + 1];
				_vPosPerPeriod_Student[i + 1] = temp2;

				break;
			}
		}
	}

	for (int i = 0; i < _vOrder.size(); i++)
	{
		_vOrder[i]->GetTransform()->SetPosition(Vector2(51, 135 - 45 * i));
	}
}

void ScheduleWindow::SetButtons()
{
	for (int i = 0; i < _vPeriods.size(); i++)
	{
		Object* period = Object::CreateObject(object);
		period->SetCameraAffected(false);
		period->SetName(_vPeriods[i]);
		period->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Schedule/" + _vPeriods[i] + ".png"));
		period->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
		period->GetTransform()->SetPosition(Vector2(51, 135 - 45 * i));
		
		_vOrder.push_back(period);

		if (period->GetName() == "Recess" || period->GetName() == "Lunch")
		{
			Object* upButton = Object::CreateObject(period);
			upButton->SetCameraAffected(false);
			upButton->SetName("Up");
			upButton->SetTag(period->GetName());
			upButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Schedule/UpButton.png"));
			upButton->GetTransform()->SetPosition(Vector2(-100, 12));
			upButton->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
			upButton->AddComponent<BoxCollider>();
			upButton->AddComponent<ChangeSchedule>();
			upButton->GetComponent<ChangeSchedule>()->AddObserver(this);

			Object* downButton = Object::CreateObject(period);
			downButton->SetCameraAffected(false);
			downButton->SetName("Down");
			downButton->SetTag(period->GetName());
			downButton->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Schedule/DownButton.png"));
			downButton->GetTransform()->SetPosition(Vector2(-100, -12));
			downButton->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
			downButton->AddComponent<BoxCollider>();
			downButton->AddComponent<ChangeSchedule>();
			downButton->GetComponent<ChangeSchedule>()->AddObserver(this);
		}
	}
}