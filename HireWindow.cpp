#include "stdafx.h"
#include "HireWindow.h"
#include "CharacterManager.h"
#include "FacultyButton.h"
#include "HireButton.h"
#include "RemoveButton.h"
#include "ButtonPoly.h"

#include <filesystem>
using namespace filesystem;

void HireWindow::Init()
{
	object->SetCameraAffected(false);

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/AvailableFaculty.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);

	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(800, -450));

	object->AddComponent<BoxCollider>();

	for (auto d : directory_iterator("Resources/Sprite/Management/Available/Faculty"))
	{
		_vFacultyNames.push_back(d.path().string().substr(46));
	}

	_characterManager = SceneManager::GetInstance()->GetNowScene()->GetChildByName("CharacterManager")->GetComponent<CharacterManager>();

	Object* hireInfo = Object::CreateObject(object);
	hireInfo->SetCameraAffected(false);
	_infoSprite = hireInfo->AddComponent<Sprite>();
	hireInfo->GetTransform()->SetScale(Vector2(1.3f, 1.3f));

	if (_sNowFacultyname.size())
	{
		_infoSprite->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/Hire" + _sNowFacultyname.top() + ".png"));
	}

	hireInfo->GetTransform()->SetPosition(Vector2(294, -10));

	_hireButton = Object::CreateObject(object);
	_hireButton->SetCameraAffected(false);
	_hireButton->AddComponent<Sprite>();
	_hireButton->GetTransform()->SetScale(Vector2(1.f, 1.f));
	_hireButton->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/Hire.png"));
	_hireButton->GetTransform()->SetPosition(Vector2(-238, -120));
	_hireButton->AddComponent<BoxCollider>();
	_hireButton->AddComponent<HireButton>();
	_hireButton->AddComponent<ButtonPoly>();

	_removeButton = Object::CreateObject(object);
	_removeButton->SetCameraAffected(false);
	_removeButton->AddComponent<Sprite>();
	_removeButton->GetTransform()->SetScale(Vector2(1.f, 1.f));
	_removeButton->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/Remove.png"));
	_removeButton->GetTransform()->SetPosition(Vector2(-50, -120));
	_removeButton->AddComponent<BoxCollider>();
	_removeButton->AddComponent<RemoveButton>();
	_removeButton->AddComponent<ButtonPoly>();

	for (int i = 0; i < _vFacultyNames.size(); i++)
	{
		_facultyButton = Object::CreateObject(object);
		_facultyButton->SetCameraAffected(false);
		_facultyButton->SetName(_vFacultyNames[i].substr(0, _vFacultyNames[i].size() - 4));
		_facultyButton->AddComponent<Sprite>();
		_facultyButton->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
		_facultyButton->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/Faculty/" + _vFacultyNames[i]));
		_facultyButton->GetTransform()->SetPosition(Vector2(-380 + i * 94, 20));
		_facultyButton->AddComponent<BoxCollider>();
		_facultyButton->AddComponent<FacultyButton>();
		_facultyButton->GetComponent<FacultyButton>()->SetHireWindowLink(this);
		_hireButton->GetComponent<HireButton>()->AddObserver(_facultyButton->GetComponent<FacultyButton>());
		_removeButton->GetComponent<RemoveButton>()->AddObserver(_facultyButton->GetComponent<FacultyButton>());
	}

	if (_sNowFacultyname.size())
	{
		_hireButton->GetComponent<HireButton>()->SetNowFacultyName(_sNowFacultyname.top());
		_removeButton->GetComponent<RemoveButton>()->SetNowFacultyName(_sNowFacultyname.top());
	}
}

void HireWindow::Update()
{
	if (_sNowFacultyname.size())
	{
		_infoSprite->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/Hire" + _sNowFacultyname.top() + ".png"));
		_hireButton->GetComponent<HireButton>()->SetNowFacultyName(_sNowFacultyname.top());
		_removeButton->GetComponent<RemoveButton>()->SetNowFacultyName(_sNowFacultyname.top());
	}
}