#pragma once
#include <Windows.h>
#include <list>
#include <map>
#include "Box2D/Box2D.h"
#include "RayCallBack.h"

using namespace std;
class Object;
class Collider;
class PhysicsManager : public b2ContactListener
{
private:
	PhysicsManager();

	b2Vec2 gravity;
	float worldToPhysicsWorld;
	float physicsWorldToWorld;
	bool drawDebug = false;
	b2World* world;
public:
	static PhysicsManager* GetInstance();
	float GetWorldToPhysicsWorld();
	float GetPhysicsWorldToWorld();

	void SetGravity(Vector2 _gravity);
	b2Vec2 GetGravity();

	void SetDrawDebug(bool _drawDebug) { drawDebug = _drawDebug; }
	bool GetDrawDebug() { return drawDebug; }

	b2Body* AddPhysicsBody(b2BodyDef* _bodyDef);
	void DeletePhysicsBody(b2Body* _body);
	b2World* GetWorld() { return world; }
	void SetWorld(b2World* _world) { world = _world; world->SetGravity(gravity);}

	virtual void BeginContact(b2Contact* contact) override;
	RayHit RayCast(Vector2 startPoint, Vector2 direction, float distance);
	virtual void EndContact(b2Contact* contact) override;
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
};

