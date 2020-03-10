#include "stdafx.h"
#include "GgaetIp.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Init()
{
	time = TimeManager::GetInstance();
	Vector2 resolution = ApplicationManager::GetInstance()->GetResolution();

	Object* mainCameraObj = Object::CreateObject();
	mainCameraObj->SetCameraAffected(false);
	mainCameraObj->SetName("mainCamera");
	mainCamera = mainCameraObj->AddComponent<Camera>();
	mainCamera->GetTransform()->SetPosition(Vector2(DesignResolution.x /2, -DesignResolution.y /2));
	mainCamera->SetDepth(0);
	CameraManager::GetInstance()->SetMainCamera(mainCamera);

	PhysicsManager* physics = PhysicsManager::GetInstance();
	physicsWorld = new b2World(physics->GetGravity());
	physicsWorld->SetAllowSleeping(true);
	physicsWorld->SetContinuousPhysics(true);
	physicsWorld->SetDebugDraw(DebugDraw::GetInstance());
	physicsWorld->SetContactListener(PhysicsManager::GetInstance());
}

Camera* Scene::GetMainCamera()
{
	return mainCamera;
}

void Scene::Release()
{
	if (SceneManager::GetInstance()->GetNowScene() == this)
	{
		willRelease = true;
		return;
	}
	//Object::Release();
}

void Scene::RunSceneInit()
{
	Scene::Init();
}

void Scene::Update()
{
	SortChildren();
	CheckMouseEvent();

	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->GetAllowsInit())
			children[i]->Init();
		children[i]->Update();
	}
	InvalidateRect(_hWnd, NULL, false);

	//if (InputManager::GetInstance()->GetKeyDown(VK_ESCAPE))
	//	exit(0);
	//if (InputManager::GetInstance()->GetKeyDown(VK_F1))
	//	PhysicsManager::GetInstance()->SetDrawDebug(!PhysicsManager::GetInstance()->GetDrawDebug());
}

extern bool Compare(Object* a, Object* b);

void Scene::Render()
{
	if (willRelease)
		return;
	Direct2D::GetInstance()->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	//sort(children.begin(), children.end(), Compare);
	for (Object* c : children)
		c->Render();
	if (PhysicsManager::GetInstance()->GetDrawDebug())
		physicsWorld->DrawDebugData();
}

void Scene::PhysicsUpdate()
{
	for (b2Body* body = physicsWorld->GetBodyList(); body; body = body->GetNext())
	{
		if (!body->GetUserData())
		{
			b2Body* deletedObject = body;
			body = body->GetNext();
			physicsWorld->DestroyBody(deletedObject);
			continue;
		}

		Transform* now = ((Object*)body->GetUserData())->GetTransform();
		if (!now->GetGameObject()->GetCameraAffected())
			continue;
		Vector2 position = now->GetWorldPosition() * PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();
		b2Vec2 physicsWorldPosition = b2Vec2(position.x, position.y);
		body->SetTransform(physicsWorldPosition, body->GetAngle());
	}
	physicsWorld->Step(TimeManager::GetInstance()->GetDeltaTime(), 8, 3); //메뉴얼 권장값
	for (b2Body* body = physicsWorld->GetBodyList(); body; body = body->GetNext())
	{
		Transform* now = ((Object*)body->GetUserData())->GetTransform();
		if (!now->GetGameObject()->GetCameraAffected())
			continue;
		Vector2 nowPosition = Vector2(body->GetPosition().x, body->GetPosition().y);
		nowPosition = nowPosition * PhysicsManager::GetInstance()->GetPhysicsWorldToWorld();
		now->SetWorldPosition(nowPosition);
		body->GetAngle()*Rad2Deg;
		now->SetRotation(-body->GetAngle()*Rad2Deg);
	}
}

LRESULT Scene::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
		case WM_ACTIVATE:
			ImGuiManager::GetInstnace()->Init();
			if (!ApplicationManager::GetInstance()->GetIsFullScreen())
				break;
			switch (LOWORD(wParam))
			{
			case WA_ACTIVE:
				ApplicationManager::GetInstance()->UpdateScreen();
				break;
			case WA_INACTIVE:
				ApplicationManager::GetInstance()->ExitFullScreen();
				break;
			}
			break;
		case WM_TIMER:
		{
			float startTime = time->GetTime();
			switch (wParam)
			{
			case 1:
			{
				this->Update();
				InputManager::GetInstance()->Update();
				PhysicsUpdate();
				SoundListenerManager::GetInstance()->Update();
				CameraManager::GetInstance()->Update();
				float deltaTime = time->GetTime() - startTime;
				if (deltaTime < 1.f / ApplicationManager::GetInstance()->GetFrameRate())
					time->SetDeltaTime(1.f / ApplicationManager::GetInstance()->GetFrameRate());
				else
					time->SetDeltaTime(deltaTime);
				if (willRelease)
					Release();
				break;
			}
			}
			break;
		}
		case WM_PAINT:
		{

			hdc = BeginPaint(hWnd, &ps);
			Direct2D::GetInstance()->GetRenderTarget()->BeginDraw();
			this->Render();
			Direct2D::GetInstance()->GetRenderTarget()->EndDraw();
			ImGuiManager::GetInstnace()->Render();
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_MOUSEMOVE:
		{
			Vector2 mousePosition = Vector2{ (float)LOWORD(lParam) ,(float)HIWORD(lParam) };
			InputManager::GetInstance()->SetMousePosition(mousePosition);
		}
		break;

		case WM_MOUSEWHEEL:
		{
			float delta = GET_WHEEL_DELTA_WPARAM(wParam);
			InputManager::GetInstance()->SetWheelDelta(!delta ? 0 : delta / abs(delta));
		}
		break;


		case WM_DESTROY:
			ApplicationManager::GetInstance()->ExitFullScreen();
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
