#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Box2D/Box2D.h"

enum BodyType
{
	StaticBody = 0,
	KinematicBody,
	DynamicBody
};

class Object;
class Transform;

class Physics : public Component
{
private:
	Transform* transform;
	Collider* collider;
	bool isGravity = false;
	bool ignoreCollision = false;

	float density = 1;			//밀도
	float friction = 0.4f;		//마찰력 0~1
	float restitution = 0;		//반발력

	Vector2 velocty;
	float gravityScale = 1.f;
	BodyType bodyType = DynamicBody;
	b2Body* body;
public:
	void SetGravityScale(float _gravityScale);
	void SetDensity(float _density);
	void SetFriction(float _friction);
	void SetRestitution(float _restitution);
	void SetBodyType(BodyType _type);
	void SetVelocty(Vector2 _velocty);
	void SetIgnoreCollision(bool _ignoreCollision);
	void SetBody(b2Body* _body);

	float GetGravityScale();
	Vector2 GetVelocty();
	float GetDensity();
	float GetFriction();
	float GetRestitution();
	bool GetIgnoreCollision();
	BodyType GetBodyType();

	void AddForce(Vector2 force);
	void SetDefaultBody();
	virtual void Init() override;
	virtual void Release() override;
	//virtual void Update() override;
};

