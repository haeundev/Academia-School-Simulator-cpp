#include "stdafx.h"
#include "GgaetIp.h"

void Physics::Init()
{
	collider = object->GetComponent<Collider>();
	transform = object->GetTransform();

	PhysicsManager* physics = PhysicsManager::GetInstance();

	if (!collider->GetBody())
		SetDefaultBody();
	else
		body = collider->GetBody();
	body->SetGravityScale(gravityScale);
}

void Physics::SetIgnoreCollision(bool _ignoreCollision)
{
	ignoreCollision = _ignoreCollision;
	if (!collider)
		return;
	body->GetFixtureList()[0].SetSensor(ignoreCollision);
}

bool Physics::GetIgnoreCollision()
{
	return ignoreCollision;
}

void Physics::SetBodyType(BodyType _bodyType)
{
	bodyType = _bodyType;
	if (!collider)
		return;
	body->SetType((b2BodyType)bodyType);
}

BodyType Physics::GetBodyType()
{
	return bodyType;
}

void Physics::SetBody(b2Body* _body)
{
	body = _body;
}

void Physics::SetDefaultBody()
{
	Vector2 position = transform->GetWorldPosition() * PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();
	b2BodyDef def;
	def.position.Set(position.x , position.y );
	def.type = (b2BodyType)bodyType;
	def.userData = object;
	def.angle = transform->GetRotation();
	body = PhysicsManager::GetInstance()->AddPhysicsBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(0.001f, 0.001f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);
}

void Physics::AddForce(Vector2 force)
{
	if (!body)
		return;
	body->ApplyForceToCenter(b2Vec2(force.x , force.y ), true);
}

void Physics::SetVelocty(Vector2 _velocty)
{
	velocty = _velocty;
	if (!collider)
		return;
	body->SetLinearVelocity(b2Vec2(velocty.x ,velocty.y ));
}

Vector2 Physics::GetVelocty()
{
	return velocty;
}

void Physics::SetGravityScale(float _gravityScale)
{
	gravityScale = _gravityScale;
	if (!collider)
		return;
	body->SetGravityScale(gravityScale);
}

float Physics::GetGravityScale()
{
	return gravityScale;
}

void Physics::SetDensity(float _density)
{
	density = _density;
}

void Physics::SetFriction(float _friction)
{
	friction = _friction;
}

void Physics::SetRestitution(float _restitution)
{
	restitution = _restitution;
}

float Physics::GetDensity()
{
	return density;
}

float Physics::GetFriction()
{
	return friction;
}

float Physics::GetRestitution()
{
	return restitution;
}

void Physics::Release()
{
	PhysicsManager::GetInstance()->DeletePhysicsBody(body);
	body = nullptr;
	Component::Release();
}