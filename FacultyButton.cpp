#include "stdafx.h"
#include "FacultyButton.h"
#include "HireWindow.h"
#include "HireButton.h"

void FacultyButton::Init()
{
	// Polydraw
	vector<Vector2> vVertices;
	vVertices.push_back(Vector2(-37, -3));
	vVertices.push_back(Vector2(37, -3));
	object->AddComponent<PolygonDraw>()->SetVertices(vVertices);
	object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.0 });
	object->GetComponent<PolygonDraw>()->SetStrokeWidth(75);
}

void FacultyButton::Update()
{
	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0.2 });
	}
	else
	{
		object->GetComponent<PolygonDraw>()->SetColor({ 1, 1, 1, 0 });
	}
}

void FacultyButton::OnMouseDown()
{
	if (_hireWindow->GetSNowFacultyName().size())
	{
		_hireWindow->GetSNowFacultyName().pop();
	}

	_hireWindow->GetSNowFacultyName().push(object->GetName());
}

void FacultyButton::OnNotify(MTYPE type, string event)
{
	if (object->GetName() != event) return;

	if (type == MTYPE::HIRED)
	{
		object->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/" + event + "_Green.png"));
	}
	if (type == MTYPE::FIRED)
	{
		object->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Management/Available/Faculty/" + event + ".png"));
	}
}