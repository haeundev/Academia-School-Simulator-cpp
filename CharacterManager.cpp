#include "stdafx.h"
#include "CharacterManager.h"
#include "Faculty.h"
#include "CharacterAnimation.h"
#include "CharacterIndex.h"
#include "TopBar.h"
#include "FacultyMove.h"
#include "WorkerMove.h"
#include "StudentMove.h"
#include "JanitorMove.h"
#include "PrincipalMove.h"
#include "NurseMove.h"
#include "Budget.h"

void CharacterManager::Init()
{
	_mFaculty.insert(pair("Dua", 0));				// Language
	_mFaculty.insert(pair("Catherine", 0));			// Math
	_mFaculty.insert(pair("Montessori", 0));		// Science
	_mFaculty.insert(pair("Hypatia", 0));			// History
	_mFaculty.insert(pair("Socrates", 0));			// Art
	_mFaculty.insert(pair("Sky", 0));				// PE

	_lStudentNames.push_back("Alden Wyrostek");
	_lStudentNames.push_back("Austin Huter");
	_lStudentNames.push_back("Barton Wzorek");
	_lStudentNames.push_back("Calvin Thurman");
	_lStudentNames.push_back("Carol Mendez");
	_lStudentNames.push_back("Cyrus Muzzillo");
	_lStudentNames.push_back("Daniel Cutierez");
	_lStudentNames.push_back("Eldon Lynch");
	_lStudentNames.push_back("Francesco Rzasa");
	_lStudentNames.push_back("George Carlo");
	_lStudentNames.push_back("Ian Muszha");
	_lStudentNames.push_back("Jewell Ryen");
	_lStudentNames.push_back("Ken Johnson");
	_lStudentNames.push_back("Marian Peterson");
	_lStudentNames.push_back("Mary Jane");
	_lStudentNames.push_back("Preston Czuba");
	_lStudentNames.push_back("Ron Gyles");
	_lStudentNames.push_back("Rose Dawson");
	_lStudentNames.push_back("Shawn Syed");
	_lStudentNames.push_back("Summer Haze");
	_lStudentNames.push_back("Tim Rylant");
	_lStudentNames.push_back("Will Brooks");
	_lStudentNames.push_back("Yun Byrnside");
	_lStudentNames.push_back("Zach Hylinski");

	for (int i = 0; i < 10; i++)
	{
		CreateWorker();
	}

	for (int i = 0; i < 24; i++)
	{
		CreateStudent();
	}

	for (auto m : _mFaculty)
	{
		CreateFaculty(m.first);
	}

	CreateNurse();

	CreatePrincipal();
}

void CharacterManager::CreateFaculty(string name)
{
	if (_mFaculty[name] > 0) return;
	
	Object* newOb = Object::CreateObject();
	newOb->SetTag("Faculty");
	newOb->SetName(name);
	newOb->AddComponent<CharacterIndex>();

	newOb->AddComponent<FacultyMove>();
	newOb->GetComponent<FacultyMove>()->SetVTilesLink(_vTiles);
	newOb->GetComponent<FacultyMove>()->SetMZonesLink(_mZones);
	newOb->GetComponent<FacultyMove>()->SetScheduleLink(_schedule);
	newOb->AddComponent<Animator>();
	newOb->AddComponent<CharacterAnimation>();

	auto newObSprite = newOb->AddComponent<Sprite>();
	newObSprite->SetSprite(ImageManager::GetInstance()->AddImage("Characters/Faculty/" + name + "_Down.png"));
	newObSprite->SetDepth((int)ZORDER::CHARACTER);
	newObSprite->GetTransform()->SetPosition(ToWorkPosition);
	
	_topBar->AddObserver(newOb->GetComponent<FacultyMove>());

	_facultyNum++;

	_mFaculty[name]++;

	_vAllCharacters.push_back(newOb);

	if (name == "Dua")
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->BudgetMinus(9100);
	else if (name == "Sky")
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->BudgetMinus(9000);
	else if (name == "Socrates")
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->BudgetMinus(9100);
	else if (name == "Hypatia")
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->BudgetMinus(8900);
	else if (name == "Catherine")
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->BudgetMinus(9000);
	else if (name == "Montessori")
		SceneManager::GetInstance()->GetNowScene()->GetChildByName("Budget")->GetComponent<Budget>()->BudgetMinus(9000);
}

void CharacterManager::CreateNurse()
{
	// Nurse는 한 명만 있을 수 있음
	if (_vNurse.size()) return;

	Object* newOb = Object::CreateObject();
	newOb->SetTag("Nurse");
	newOb->SetName("Nurse");
	newOb->AddComponent<CharacterIndex>();
	newOb->AddComponent<NurseMove>();
	newOb->GetComponent<NurseMove>()->SetVTilesLink(_vTiles);
	newOb->AddComponent<Animator>();
	newOb->AddComponent<CharacterAnimation>();

	auto newObSprite = newOb->AddComponent<Sprite>();
	newObSprite->SetSprite(ImageManager::GetInstance()->AddImage("Characters/Nurse/Nurse_Down.png"));
	newObSprite->SetDepth((int)ZORDER::CHARACTER);
	newObSprite->GetTransform()->SetPosition(ToWorkPosition);

	_vNurse.push_back(newOb);

	_vStaff.push_back(newOb);

	_vAllCharacters.push_back(newOb);

	_topBar->AddObserver(newOb->GetComponent<NurseMove>());

}

void CharacterManager::CreatePrincipal()
{
	// Principal은 한 명만 있을 수 있음
	if (_vPrincipal.size()) return;

	Object* newOb = Object::CreateObject();
	newOb->SetTag("Principal");
	newOb->SetName("Principal");
	newOb->AddComponent<CharacterIndex>();
	newOb->AddComponent<PrincipalMove>();
	newOb->GetComponent<PrincipalMove>()->SetVTilesLink(_vTiles);
	newOb->AddComponent<Animator>();
	newOb->AddComponent<CharacterAnimation>();
	
	auto newObSprite = newOb->AddComponent<Sprite>();
	newObSprite->SetSprite(ImageManager::GetInstance()->AddImage("Characters/Principal/Principal_Down.png"));
	newObSprite->SetDepth((int)ZORDER::CHARACTER);
	newObSprite->GetTransform()->SetPosition(ToWorkPosition);

	_vPrincipal.push_back(newOb);

	_vStaff.push_back(newOb);

	_vAllCharacters.push_back(newOb);

	_topBar->AddObserver(newOb->GetComponent<PrincipalMove>());

}

void CharacterManager::CreateStudent()
{
	if (!_lStudentNames.size()) return;
	
	_sNum++;

	Object* newOb = Object::CreateObject();
	newOb->SetTag("Student" + to_string(_sNum));
	newOb->SetName(_lStudentNames.front());
	newOb->AddComponent<CharacterIndex>();
	newOb->AddComponent<StudentMove>();
	newOb->GetComponent<StudentMove>()->SetVTilesLink(_vTiles);
	newOb->GetComponent<StudentMove>()->SetScheduleLink(_schedule);
	newOb->AddComponent<Animator>();
	newOb->AddComponent<CharacterAnimation>();
	
	auto newObSprite = newOb->AddComponent<Sprite>();
	newObSprite->SetSprite(ImageManager::GetInstance()->AddImage("Characters/Students/" + _lStudentNames.front() + "_Down.png"));
	newObSprite->SetDepth((int)ZORDER::CHARACTER);
	newObSprite->GetTransform()->SetPosition(Vector2(ToSchoolPosition));
	_vStudents.push_back(newOb);

	_lStudentNames.pop_front();

	_topBar->AddObserver(newOb->GetComponent<StudentMove>());

	_vAllCharacters.push_back(newOb);
}

void CharacterManager::CreateWorker()
{
	if (_wNum > 10) return;

	Object* newOb = Object::CreateObject();
	newOb->SetTag("Worker");
	newOb->SetName(to_string(_wNum));
	newOb->AddComponent<CharacterIndex>();
	newOb->AddComponent<WorkerMove>();
	newOb->GetComponent<WorkerMove>()->SetVTilesLink(_vTiles);
	newOb->GetComponent<WorkerMove>()->SetMapToolLink(_mapTool);
	newOb->AddComponent<Animator>();
	newOb->AddComponent<CharacterAnimation>();

	auto newObSprite = newOb->AddComponent<Sprite>();
	newObSprite->SetSprite(ImageManager::GetInstance()->AddImage("Characters/Worker/" + to_string(_wNum) + "_Down.png"));
	newObSprite->SetDepth((int)ZORDER::CHARACTER);
	newObSprite->GetTransform()->SetPosition(ToWorkPosition);
	_vWorkers.push_back(newOb);
	_vStaff.push_back(newOb);

	_wNum++;

	_vAllCharacters.push_back(newOb);
}

void CharacterManager::CreateJanitor()
{
	if (_jNum > 4) return;
	
	_jNum++;

	Object* newOb = Object::CreateObject();
	newOb->SetTag("Janitor");
	newOb->SetName(to_string(_jNum));
	newOb->AddComponent<CharacterIndex>();
	newOb->AddComponent<JanitorMove>();
	newOb->GetComponent<JanitorMove>()->SetVTilesLink(_vTiles);
	newOb->AddComponent<Animator>();
	newOb->AddComponent<CharacterAnimation>();

	auto newObSprite = newOb->AddComponent<Sprite>();
	newObSprite->SetSprite(ImageManager::GetInstance()->AddImage("Characters/Janitor/" + to_string(_jNum % 5 + 1) + "_Down.png"));
	newObSprite->SetDepth((int)ZORDER::CHARACTER);
	newObSprite->GetTransform()->SetPosition(ToWorkPosition);
	_vStaff.push_back(newOb);

	_vAllCharacters.push_back(newOb);
}

void CharacterManager::FireFaculty(string name)
{
	if (_mFaculty[name] == 0) return;
	
	_mFaculty[name]--;

	_facultyNum--;

	SceneManager::GetInstance()->GetNowScene()->GetChildByName(name)->SetIsActive(false);
}

void CharacterManager::FireNurse()
{
	if (!_vNurse.size()) return;

	_vNurse.pop_back();
}

void CharacterManager::ExpelStudent(Object* object)
{
	object->SetIsActive(false);

	_lStudentNames.push_back(object->GetName());
}

void CharacterManager::FireWorker()
{
	object->SetIsActive(false);

	_wNum--;

	_vWorkers.pop_back();
}

void CharacterManager::FireJanitor()
{
	object->SetIsActive(false);

	_jNum--;

	_vJanitors.pop_back();
}

void CharacterManager::OnNotify(MTYPE type, string event)
{
	if (type != MTYPE::STAR || event != "SetLink") return;

	for (auto v : _vAllCharacters)
	{
		if (v->GetTag() == "Worker")
		{
			v->GetComponent<WorkerMove>()->SetVTilesLink(_vTiles);
		}
		else if (v->GetTag() == "Faculty")
		{
			v->GetComponent<FacultyMove>()->SetVTilesLink(_vTiles);
		}
		else if (v->GetTag() == "Janitor")
		{
			v->GetComponent<JanitorMove>()->SetVTilesLink(_vTiles);
		}
		else if (v->GetTag() == "Student")
		{
			v->GetComponent<StudentMove>()->SetVTilesLink(_vTiles);
		}
	}
}
