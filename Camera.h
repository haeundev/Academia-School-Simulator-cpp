#pragma once
#include "Component.h"

class Transform;
class Camera : public Component
{
private:
	Transform* transform;
	int depth;
public:
	void SetDepth(int depth) { this->depth = depth; };
	int GetDepth() { return depth; };

	Transform* GetTransform() { return transform; };
	virtual void Awake() override;
	virtual void Release() override;
};

