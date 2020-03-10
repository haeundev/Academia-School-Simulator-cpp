#include "stdafx.h"
#include "GgaetIp.h"

Collider::Collider()
{
	filter.maskBits = 0xFFFF;
	filter.categoryBits = 0x0001;
}

b2Body* Collider::GetBody()
{
	return body;
}

void Collider::Update()
{
	if (!object->GetIsActive())
		return;
}
void Collider::Awake()
{
	transform = object->GetTransform();
}

void Collider::Init()
{
	physicsComponent = object->GetComponent<Physics>();
}

void Collider::OnMouseDown()
{
	for (auto c : transform->GetGameObject()->GetComponents<Script>())
		c->OnMouseDown();
}

void Collider::OnMouseUp()
{
	for (auto c : transform->GetGameObject()->GetComponents<Script>())
		c->OnMouseUp();
}


void Collider::SetFilter(b2Filter _filter)
{
	filter = _filter;
	if (fixture)
		fixture->SetFilterData(filter);
}

void Collider::Release()
{
	if (physicsComponent)
		physicsComponent->SetBody(nullptr);
	Component::Release();
}