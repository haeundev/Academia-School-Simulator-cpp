#include "stdafx.h"
#include "RayHit.h"
#include "PhysicsManager.h"

RayHit::RayHit(b2Fixture * fixture, Vector2 collisionPoint, Vector2 normalVector)
{
	for (auto f = fixture; f != nullptr; f = f->GetNext())
		_fixtures.push_back(fixture);
	_collisionPoint = collisionPoint * PhysicsManager::GetInstance()->GetPhysicsWorldToWorld();
	_normalVector = normalVector * PhysicsManager::GetInstance()->GetPhysicsWorldToWorld();
}
