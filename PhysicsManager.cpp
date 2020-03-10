#include "stdafx.h"
#include "GgaetIp.h"

PhysicsManager* PhysicsManager::GetInstance()
{
	static PhysicsManager* instance = new PhysicsManager();
	return instance;
}

PhysicsManager::PhysicsManager()
{
	gravity = b2Vec2(0, 9.8f);
	worldToPhysicsWorld = 10.f / ApplicationManager::GetInstance()->GetResolution().y ;
	physicsWorldToWorld = ApplicationManager::GetInstance()->GetResolution().y  / 10;
}

b2Vec2 PhysicsManager::GetGravity()
{
	return gravity;
}

float PhysicsManager::GetPhysicsWorldToWorld()
{
	return physicsWorldToWorld;
}

void PhysicsManager::SetGravity(Vector2 _gravity)
{
	gravity = b2Vec2(_gravity.x ,_gravity.y );
	world->SetGravity(gravity);
}

b2Body* PhysicsManager::AddPhysicsBody(b2BodyDef* _bodyDef)
{
	return world->CreateBody(_bodyDef);
}

void PhysicsManager::DeletePhysicsBody(b2Body* body)
{
	body->SetUserData(nullptr);
}



float PhysicsManager::GetWorldToPhysicsWorld()
{
	return worldToPhysicsWorld;
}

void PhysicsManager::BeginContact(b2Contact* contact)
{
	Object* a = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
	Object* b = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (!a || !b)
		return;

	for (Script* s : a->GetComponents<Script>())
		s->OnCollisionEnter(b);
	for (Script* s : b->GetComponents<Script>())
		s->OnCollisionEnter(a);
}

RayHit PhysicsManager::RayCast(Vector2 startPoint, Vector2 direction, float distance)
{
	auto rayCallBack = new RayCallBack();
	Vector2 startPoint_World = startPoint * worldToPhysicsWorld;
	Vector2 endPoint_World = (startPoint + direction * distance) * worldToPhysicsWorld;
	b2Vec2 start = { startPoint_World.x,startPoint_World.y };
	b2Vec2 end = { endPoint_World.x,endPoint_World.y };
	world->RayCast(rayCallBack, start, end);
	//if (isDebug)
	//	DebugDraw::GetInstance()->DrawLine(startPoint, startPoint + direction * distance);
	return rayCallBack->GetHitInfo();
}


void PhysicsManager::EndContact(b2Contact* contact)
{
	Object* a = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
	Object* b = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();

	if (!a || !b)
		return;
	
	for (Script* s : a->GetComponents<Script>())
		s->OnCollisionExit(b);
	for (Script* s : b->GetComponents<Script>())
		s->OnCollisionExit(a);
}

void PhysicsManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	Object* a = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
	Object* b = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();

	if (!a || !b)
		return;
	
	for (Script* s : a->GetComponents<Script>())
		s->OnCollisionStay(b);
	for (Script* s : b->GetComponents<Script>())
		s->OnCollisionStay(a);
}