#include "stdafx.h"
#include "StartSchoolYear.h"
#include "TopBar.h"
#include "AdmissionWindow.h"

void StartSchoolYear::Init()
{
	object->AddComponent<BoxCollider>();
	object->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("UI/TopMenu/StartSchoolYear.png"));
	object->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_WINDOW);
	object->GetComponent<Sprite>()->SetOpacity(0);
	object->GetTransform()->SetPosition(Vector2(300, -60));

	// Polydraw
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-90, 0));
	vVertices.push_back(Vector2(90, 0));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(30);
	object->GetComponent<PolygonDraw>()->SetDepth((int)ZORDER::POLY_ON_UI);
}

void StartSchoolYear::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		if (_topBar->GetPhase() == PHASE::BUILD_PHASE && _admissionWindow->GetTotalNum() >= 20)
		{
			object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.3 });

			if (InputManager::GetInstance()->GetKeyDown(VK_LBUTTON))
			{
				_topBar->SetPhase(PHASE::PLAY_PHASE);
				_topBar->AddGameDayCount();
			}
		}
	}
	else if(!object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0 });
	}
}