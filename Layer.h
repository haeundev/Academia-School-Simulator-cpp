#pragma once
#include <d2d1.h>
#include <d2d1_1.h>
#include "Vector2.h"
#include <memory>

class Layer
{
private:
	Vector2 position;
	ID2D1Layer* layer;
	Vector2 size;
	Layer() {};
public:
	static std::shared_ptr<Layer> CreateLayer(Vector2 size = Vector2::zero,Vector2 position = Vector2::zero);

	Vector2 GetSize() { return size; }
	ID2D1Layer* GetLayer(){ return layer; }
	Vector2 GetPosition() { return position; }
	void SetPosition(Vector2 position) { this->position = position; }
	~Layer();
};

