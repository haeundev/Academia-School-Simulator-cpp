#include "stdafx.h"
#include "C1_Window.h"
#include "C2_Window.h"
#include "C2_Button.h"
#include "ControlCamera.h"
#include <filesystem>
using namespace filesystem;


void C2_Window::Init()
{
	object->SetCameraAffected(false);

	object->AddComponent<BoxCollider>();

	_sprite = object->GetComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("UI/Category2Window.png"));
	_sprite->SetDepth((int)ZORDER::UI_WINDOW);
	_transform = object->GetTransform();
	_transform->SetPosition(Vector2(325, -992));

	for (auto d : directory_iterator("Resources/Sprite/UI/C2_Buttons/" + _C2WindowTag))
	{
		_vButtonsForC2.push_back(d.path().string().substr(32 + _C2WindowTag.size()));
	}

	AddButtons();

	_camera = _c1Window->GetComponent<C1_Window>()->GetCamera();
}

void C2_Window::Update()
{
	StopZoomAndJustScroll();

	mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
	mouseWorldPosition = Matrix3x3::Mul(mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
	mouseX = mouseWorldPosition.x;
	mouseY = (-1) * mouseWorldPosition.y;

	_currentIndex.x = (int)(mouseX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - mouseY) / GridHeight;
}

void C2_Window::StopZoomAndJustScroll()
{
	if (object->GetName() == "Build") return;

	if (object->GetComponent<BoxCollider>()->PtInCollider(InputManager::GetInstance()->GetMouseWorldPosition()))
	{
		_camera->GetComponent<ControlCamera>()->SetCanZoom(false);

		// 스크롤 영역을 만들기
		_delta = InputManager::GetInstance()->GetWheelDelta();

		if (!_delta) return;
		if (_transform->GetPosition().y < -975)
			_transform->SetPosition(Vector2(_transform->GetPosition().x, -975));

		if (object->GetName() == "Zones")
		{
			if (_transform->GetPosition().y > -940)
				_transform->SetPosition(Vector2(_transform->GetPosition().x, -940));
		}
		if (object->GetName() == "Objects")
		{
			if (_transform->GetPosition().y > -740)
				_transform->SetPosition(Vector2(_transform->GetPosition().x, -740));
		}

		_transform->Translate(Vector2(0, _delta * _scrollSpeed));
	}
	else
	{
		_camera->GetComponent<ControlCamera>()->SetCanZoom(true);
	}

	_sprite->SetFrameSize(Vector2(250,600));

	if (_transform->GetWorldPosition().y > 196)
	{
		_sprite->SetStartPoint(Vector2(0, abs(_transform->GetWorldPosition().y - (196))));
	}
}

void C2_Window::AddButtons()
{
	for (int i = 0; i < _vButtonsForC2.size(); i++)
	{
		Object* button = Object::CreateObject(object);
		button->SetCameraAffected(false);
		button->SetTag(object->GetName());
		button->SetName(_vButtonsForC2[i].substr(0, _vButtonsForC2[i].size() - 4));
		button->AddComponent<Sprite>();
		button->GetComponent<Sprite>()->SetSprite(ImageManager::GetInstance()
			->AddImage("UI/C2_Buttons/" + _C2WindowTag + "/" + _vButtonsForC2[i]));
		button->GetComponent<Sprite>()->SetDepth((int)ZORDER::UI_BUTTONS_ON_WINDOW);
		button->GetTransform()->SetPosition(Vector2(0, 270 - i * 35));
		button->AddComponent<BoxCollider>();
		button->AddComponent<C2_Button>();
		button->GetComponent<Sprite>()->SetLayer(Layer::CreateLayer(Vector2(250, 300), Vector2(-470, -395)));
	}
}