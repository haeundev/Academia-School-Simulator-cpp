#include "stdafx.h"
#include "DrawLine.h"

void DrawLine::Init()
{
	Object* lineObj = Object::CreateObject();
	line = lineObj->AddComponent<LineComponent>();
	line->SetSize(3);
	line->SetColor(color);
	line->SetDepth(-1);
}

void DrawLine::Release()
{
	line->GetGameObject()->Release();
	ScriptComponent::Release();
}

void DrawLine::Update()
{
	line->SetPosition(obj[0]->GetTransform()->GetWorldPosition(), obj[1]->GetTransform()->GetWorldPosition());
}

void DrawLine::SetObject(int number, Object* obj)
{
	if (!number)
		this->obj[0] = obj;
	else
		this->obj[1] = obj;
}

void DrawLine::SetLine(int number)
{
	switch (number)
	{
	case 1:
		color = { 0,0.3f,1,0.6f };
		break;
	case 2:
		color = { 1,0.1f,0,0.6f };
		break;
	case 3:
		color = { 0.7F,0.8f,1,0.6f };
		break;
	case 4:
		color={ 0.6f,1,0.3f,0.6f };
		break;
	}
}