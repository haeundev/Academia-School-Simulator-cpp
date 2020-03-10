#include "stdafx.h"
#include "GgaetIp.h"

void CircleCollider::Update()
{
	Collider::Update();
	UpdateBody();
}

bool CircleCollider::PtInCollider(Vector2 point)
{
	Transform* cameraTransform = CameraManager::GetInstance()->GetRenderCamera()->GetTransform();
	RECT rect = transform->GetRect();
	Vector3 worldPointPosition = Vector3(point.x, point.y, 1);
	worldPointPosition = Matrix3x3::Mul(worldPointPosition, cameraTransform->GetLocalToWorldMatrix().GetInverseMatrix());
	Vector2 pointPosition = Vector2(worldPointPosition.x,worldPointPosition.y);

	Vector2 distance = transform->GetWorldPosition();
	distance -= pointPosition;
	return distance.Magnitude() < radius;
}

void CircleCollider::Init()
{
	Collider::Init();
	RECT rect = transform->GetRect();
	Vector2 scale = transform->GetScale();

	Vector2 position = transform->GetWorldPosition()*PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();

	b2BodyDef bodyDef;
	bodyDef.angle = transform->GetRotation()*Deg2Rad;
	bodyDef.position.Set(position.x , position.y );
	bodyDef.userData = object;
	if (physicsComponent != nullptr)
		bodyDef.type = (b2BodyType)physicsComponent->GetBodyType();
	else
		bodyDef.type = b2BodyType::b2_staticBody;
	body = PhysicsManager::GetInstance()->AddPhysicsBody(&bodyDef);

	Vector2 size = Vector2(rect.right - rect.left, rect.bottom - rect.top);
	size = size * scale * PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();

	b2CircleShape shape;
	shape.m_radius = radius;
	shape.m_p.Set(position.x , position.y );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	if (physicsComponent != nullptr)
	{
		fixtureDef.density = physicsComponent->GetDensity();
		fixtureDef.friction = physicsComponent->GetFriction();
		fixtureDef.restitution = physicsComponent->GetRestitution();
		fixtureDef.isSensor = physicsComponent->GetIgnoreCollision();
	}
	else
	{
		fixtureDef.density = 1;
		fixtureDef.friction = 0.5f;
		fixtureDef.restitution = 0;
		fixtureDef.isSensor = false;
	}

	body->CreateFixture(&fixtureDef);
}

void CircleCollider::UpdateBody()
{
	Vector2 position = transform->GetWorldPosition()*PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();
	b2Vec2 physicsWorldPosition = b2Vec2(position.x , position.y );
	body->SetTransform(physicsWorldPosition, body->GetAngle());
}

void CircleCollider::Release()
{
	//SceneManager::GetInstance()->GetNowScene()->DeletePhysicsBody(body);
	Collider::Release();
}