#pragma once
#include "Collider.h"

class Vector2;
class BoxCollider : public Collider
{
private:
	Vector2 size;
	bool synchronizeSprite = true;
public:
	BoxCollider();
	void SetSize(Vector2 _size);
	Vector2 GetSize();
	void UpdateSize();
	virtual void Update() override;
	virtual void Init() override;
	virtual void Release() override;
	virtual bool PtInCollider(Vector2 point) override;
};

