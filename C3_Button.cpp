#include "stdafx.h"
#include "C3_Button.h"
#include "FollowMouseSprite.h"
#include "DrawZones.h"
#include "CharacterManager.h"
#include "ObjectData.h"
#include <filesystem>
using namespace filesystem;

void C3_Button::Init()
{
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-27, 14));
	vVertices.push_back(Vector2(27, 14));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(54);
	object->GetComponent<PolygonDraw>()->SetDepth(1);

	_clickedImageName = "transparentTile";

	_scene = SceneManager::GetInstance()->GetNowScene();
	_characterManager = _scene->GetChildByName("CharacterManager")->GetComponent<CharacterManager>();

	if (object->GetTag() == "Build" || object->GetTag() == "Objects")
	{
		_costInfo = Object::CreateObject(object);
		_costInfo->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/CostBox.png"));
		_costInfo->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW);
		_costInfo->GetComponent<Sprite>()->SetOpacity(0.7);
		_costInfo->GetTransform()->SetPosition(Vector2(55, 65));

		_cost = SceneManager::GetInstance()->GetNowScene()->GetChildByName("ObjectData")
			->GetComponent<ObjectData>()->GetMAttributeData()[object->GetName()].cost;

		_costInfoText = Object::CreateObject(_costInfo);
		_costInfoText->AddComponent<Text>()->CreateText(to_wstring(_cost), L"Times New Roman", L"ko-KR", { 1,1,1,1 }, 20, 60, 40);
		_costInfoText->GetComponent<Text>()->SetDepth((int)ZORDER::UI_TEXTS_ON_WINDOW + 1);
		_costInfoText->GetComponent<Text>()->SetColor({ 1.f, 1.f, 0.f, 1.0f }, 0, to_string(_cost).length());
		_costInfoText->GetTransform()->SetPosition(Vector2(21, -8));

		_costInfo->SetCameraAffected(false);
		_costInfoText->SetCameraAffected(false);
	}
}

void C3_Button::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.2 });

		if (object->GetTag() == "Build" || object->GetTag() == "Objects")
		{
			_costInfo->SetIsActive(true);
		}
	}
	else
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0 });

		if (object->GetTag() == "Build" || object->GetTag() == "Objects")
		{
			_costInfo->SetIsActive(false);
		}
	}
}

void C3_Button::OnMouseDown()
{
	if (object->GetTag() == "Build"	|| object->GetTag() == "Objects")
	{
		_clickedImageName = object->GetName();		// Chalkboard, Table, Chair, ...

		if (_scene->GetChildByName("Mouse")->GetComponent<FollowMouseSprite>()->GetSStoreImgKey().size())
		{
			_scene->GetChildByName("Mouse")->GetComponent<FollowMouseSprite>()->GetSStoreImgKey().pop();
		}

		_scene->GetChildByName("Mouse")->GetComponent<FollowMouseSprite>()->GetSStoreImgKey().push(_clickedImageName);
	}
	else if (object->GetTag() == "Zones")
	{
		_clickedImageName = object->GetName();		// Office, Classroom, Cafeteria, ...

		if (_scene->GetChildByName("DrawZones")->GetComponent<DrawZones>()->GetSStoreZoneKey().size())
		{
			_scene->GetChildByName("DrawZones")
				->GetComponent<DrawZones>()->GetSStoreZoneKey().pop();
		}

		_scene->GetChildByName("DrawZones")->GetComponent<DrawZones>()->GetSStoreZoneKey().push(_clickedImageName);
	}
	else if (object->GetName() == "Nurse")
	{
		_characterManager->CreateNurse();
	}
	else if (object->GetName() == "Principal")
	{
		_characterManager->CreatePrincipal();
	}
	else if (object->GetName() == "Janitor")
	{
		_characterManager->CreateJanitor();
	}
	else if (object->GetName() == "Worker")
	{
		_characterManager->CreateWorker();
	}
}