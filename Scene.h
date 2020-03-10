#pragma once
#include "Object.h"
#include "Box2D/Box2D.h"

class Direct2D;
class TimeManager;
class ApplicationManager;
class Scene : public Object
{
private:
	TimeManager* time;
	Camera* mainCamera;
	b2World* physicsWorld;
	bool willRelease = false;

	void PhysicsUpdate();
public:
	Scene();
	virtual ~Scene();

	void RunSceneInit();
	virtual void Init() override;			
	virtual void Release() override;		
	virtual void Update() override final;	
	virtual void Render() override final;	

	Camera* GetMainCamera();

	b2World* GetWorld() { return physicsWorld; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};
