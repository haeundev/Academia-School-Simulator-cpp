#pragma once
#include "Component.h"

enum class DrawType
{
	Sprite,
	Text
};

class Transform;
class Layer;

class DrawComponent : public Component
{
protected:
	Transform* transform;
	bool isCamearAffected = true;
	shared_ptr<Layer> layer;
	DrawComponent();

public:
	Transform* GetTransform() { return transform; };
	void SetCameraAffected(bool affected) { isCamearAffected = affected; object->SetCameraAffected(isCamearAffected); };
	bool GetCameraAffected() { return isCamearAffected; };
	virtual void Awake() override;
	void SetDepth(int _depth);
	int GetDepth();

	void SetLayer(shared_ptr<Layer> layer);
	shared_ptr<Layer> GetLayer();
};

