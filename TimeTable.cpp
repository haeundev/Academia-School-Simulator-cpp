#include "stdafx.h"
#include "TimeTable.h"

void TimeTable::Init()
{
	object->AddComponent<BoxCollider>();
	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/Homeroom.png"));
	_sprite->GetTransform()->SetPosition(Vector2(1355, -18));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);

	// Polydraw
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-70, 0));
	vVertices.push_back(Vector2(75, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 0.4, 0.6, 1, 0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(35);
	object->GetComponent<PolygonDraw>()->SetDepth((int)ZORDER::POLY_ON_UI);

	_descriptionBox = Object::CreateObject();
	_descriptionBox->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/Description/TimeTableInfo.png"));
	_descriptionBox->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
	_descriptionBox->GetTransform()->SetPosition(Vector2(1295, -65));
	_descriptionBox->SetCameraAffected(false);
}

void TimeTable::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 0.4, 0.8, 1, 0.3 });
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0.85);
	}
	else
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 0.4, 0.6, 1, 0 });
		_descriptionBox->GetComponent<Sprite>()->SetOpacity(0);
	}
}

void TimeTable::OnNotify(MTYPE type, string event)
{
	if (type != MTYPE::TIME) return;
	
	if (event == "Homeroom_StaffIn")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/Homeroom.png"));
	}
	if (event == "FirstPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/FirstPeriod.png"));
	}
	if (event == "SecondPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/SecondPeriod.png"));
	}
	if (event == "ThirdPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/ThirdPeriod.png"));
	}
	if (event == "FourthPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/FourthPeriod.png"));
	}
	if (event == "FifthPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/FifthPeriod.png"));
	}
	if (event == "SixthPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/SixthPeriod.png"));
	}
	if (event == "SeventhPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/SeventhPeriod.png"));
	}
	if (event == "EighthPeriod")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/EighthPeriod.png"));
	}
	if (event == "Dismissal_AllOut")
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/TimeTable/Dismissal.png"));
	}
}