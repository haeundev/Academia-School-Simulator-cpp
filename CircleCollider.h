#pragma once
#include "Collider.h"

class Vector2;
class CircleCollider : public Collider
{
private:
	void UpdateBody();
	float radius;
public:
	void SetRadius(float _radius);
	float GetRadius();
	virtual void Update() override;
	virtual void Init() override;
	virtual void Release() override;
	virtual bool PtInCollider(Vector2 point) override;
};

