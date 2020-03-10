#pragma once
#include "DrawComponent.h"
#include "Vector2.h"
#include <memory>
#include "Image.h"

class Transform;

class Sprite : public DrawComponent
{
private:
	shared_ptr<Image> image;

	Vector2 startPoint;
	Vector2 frameSize;

	float opacity = 1;
	bool isFliping = false;
public:
	virtual void Render() override;
	virtual void Awake() override;
	virtual void Release() override;

	Vector2 GetStartPoint();
	Vector2 GetFrameSize();

	void SetStartPoint(Vector2 startPoint);
	void SetFrameSize(Vector2 frameSize);
	void SetFlip(bool flip);
	void SetOpacity(float opacity) { this->opacity = opacity; };
	float GetOpacity() { return opacity; };

	void SetSprite(shared_ptr<Image> image);
	shared_ptr<Image> GetSprite();
};

