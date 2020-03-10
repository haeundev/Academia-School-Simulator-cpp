#include "stdafx.h"
#include "GameScene.h"

#include "DrawGrid.h"
#include "ControlCamera.h"
#include "C1_Window.h"
#include "Mouse.h"
#include "MapTool.h"
#include "TopBar.h"
#include "Tile.h"
#include "TilePolyDraw.h"
#include "FollowMouseSprite.h"
#include "ObjectData.h"
#include "DrawZones.h"
#include "CharacterManager.h"
#include "Budget.h"
#include "Department.h"
#include "TimeTable.h"
#include "Schedule.h"
#include "RealtimePoly.h"
#include "AStar.h"
#include "BudgetNotification.h"
#include "Guideline.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

void GameScene::Init()
{
	ShowCursor(false);

	for (int i = 0; i < TotalGridX * TotalGridY; i++)
	{
		Object* tile = Object::CreateObject();
		auto tileCompo = tile->AddComponent<Tile>();
		tileCompo->SetIndex(Vector2(i % TotalGridX, i / TotalGridY));
		tileCompo->SetAttribute(ATTRIBUTE::TILE_NONE);

		tile->GetTransform()->SetPosition(Vector2(tileCompo->GetIndex().x * GridWidth + GridWidth  + GRID_STARTPOINT.x,
			-(tileCompo->GetIndex().y * GridHeight) - GridHeight + GRID_STARTPOINT.y));

		_vTiles.push_back(tile);
	}

	//Object* mainBGM = Object::CreateObject();
	//mainBGM->AddComponent<Sound>()->SetSound(AudioClip::CreateSound("MainBG.mp3"));
	//mainBGM->GetComponent<Sound>()->GetAudioClip()->SetVolume(1.f);
	//mainBGM->GetComponent<Sound>()->Play();

	Object* camera = Object::CreateObject();
	camera->AddComponent<ControlCamera>();

	Object* c1_Window = Object::CreateObject();
	c1_Window->AddComponent<BoxCollider>();
	c1_Window->AddComponent<C1_Window>();
	c1_Window->GetComponent<C1_Window>()->SetCameraLink(camera);

	Object* defaultBackground = Object::CreateObject();
	defaultBackground->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("DefaultBackground.png"));
	defaultBackground->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + GridWidth * TotalGridX / 2 - GridWidth / 2, 
			GRID_STARTPOINT.y - GridHeight * TotalGridY / 2 + GridHeight / 2));

	Object* guideline = Object::CreateObject();
	guideline->SetName("Guideline");
	guideline->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("BuildGuideline.png"));
	guideline->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + GridWidth * TotalGridX / 2 - GridWidth / 2,
			GRID_STARTPOINT.y - GridHeight * TotalGridY / 2 + GridHeight / 2));
	guideline->GetComponent<Sprite>()->SetDepth((int)ZORDER::GUIDELINE);
	guideline->GetComponent<Sprite>()->SetOpacity(0.f);
	guideline->AddComponent<Guideline>();

	Object* guidefloor = Object::CreateObject();
	guidefloor->SetName("GuideFloor");
	guidefloor->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("BuildGuideline3.png"));
	guidefloor->GetComponent<Sprite>()->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + GridWidth * TotalGridX / 2 - GridWidth / 2,
			GRID_STARTPOINT.y - GridHeight * TotalGridY / 2 + GridHeight / 2));
	guidefloor->GetComponent<Sprite>()->SetDepth((int)ZORDER::FLOOR);
	guidefloor->GetComponent<Sprite>()->SetOpacity(0.f);
	guidefloor->AddComponent<Guideline>();

	Object* mouse = Object::CreateObject();
	mouse->AddComponent<Mouse>();
	mouse->SetName("Mouse");

	Object* timeTable = Object::CreateObject();
	timeTable->AddComponent<TimeTable>();
	timeTable->SetCameraAffected(false);

	Object* characterManager = Object::CreateObject();
	characterManager->AddComponent<CharacterManager>();
	characterManager->SetName("CharacterManager");

	Object* topBar = Object::CreateObject();
	topBar->AddComponent<TopBar>();
	topBar->SetName("TopBar");
	topBar->GetComponent<TopBar>()->AddObserver(timeTable->GetComponent<TimeTable>());
	topBar->GetComponent<TopBar>()->SetCMLink(characterManager->GetComponent<CharacterManager>());

	characterManager->GetComponent<CharacterManager>()->SetTopBarLink(topBar->GetComponent<TopBar>());

	Object* department = Object::CreateObject();
	department->AddComponent<Department>();

	Object* schedule = Object::CreateObject();
	schedule->AddComponent<Schedule>();
	characterManager->GetComponent<CharacterManager>()->SetScheduleLink(schedule->GetComponent<Schedule>());

	Object* budget = Object::CreateObject();
	budget->SetName("Budget");
	budget->AddComponent<Budget>();

	Object* budgetNotification = Object::CreateObject();
	budgetNotification->AddComponent<BudgetNotification>();


	Object* objectData = Object::CreateObject();
	objectData->AddComponent<ObjectData>();
	objectData->SetName("ObjectData");

	characterManager->GetComponent<CharacterManager>()->SetVTilesLink(&_vTiles);

	Object* mapTool = Object::CreateObject();
	mapTool->AddComponent<MapTool>();
	mapTool->SetName("MapTool");
	mapTool->GetComponent<MapTool>()->SetVTilesLink(&_vTiles); 
	mapTool->GetComponent<MapTool>()->SetAttributeInfoLink(objectData->GetComponent<ObjectData>());
	mapTool->GetComponent<MapTool>()->SetBudgetLink(budget->GetComponent<Budget>());

	characterManager->GetComponent<CharacterManager>()->SetMapToolLink(mapTool->GetComponent<MapTool>());
	
	Object* tilePoly = Object::CreateObject();
	tilePoly->AddComponent<TilePolyDraw>();
	tilePoly->GetComponent<TilePolyDraw>()->SetVTilesLink(&_vTiles);
	tilePoly->SetIsActive(false);

	Object* followMouseSprite = Object::CreateObject();
	followMouseSprite->AddComponent<FollowMouseSprite>();
	followMouseSprite->SetName("Mouse");

	tilePoly->GetComponent<TilePolyDraw>()->SetFollowMouseSpriteLink(followMouseSprite->GetComponent<FollowMouseSprite>());
	mapTool->GetComponent<MapTool>()->SetFollowMouseSpriteLink(followMouseSprite->GetComponent<FollowMouseSprite>());

	mapTool->GetComponent<MapTool>()->AddObserver(budgetNotification->GetComponent<BudgetNotification>());

	Object* drawZones = Object::CreateObject();
	drawZones->AddComponent<DrawZones>();
	drawZones->SetName("DrawZones");
	drawZones->GetComponent<DrawZones>()->SetVTilesLink(&_vTiles);

	characterManager->GetComponent<CharacterManager>()->SetMZonesLink(drawZones->GetComponent<DrawZones>()->GetMZones());
}