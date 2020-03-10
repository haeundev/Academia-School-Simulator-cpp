#pragma once
#include "Component.h"
#include <d2d1.h>
#include "Vector2.h"
#include "Matrix3x3.h"
class Matrix3x3;

class Transform : public Component
{
private:
	Vector2 anchorPoint;
	Vector2 position;
	Vector2 scale;
	D2D1_RECT_F size = D2D1::RectF();
	RECT rect;
	float rotation;
	int depth = 0;

	Matrix3x3 scaleMatrix;
	Matrix3x3 rotateMatrix;
	Matrix3x3 translateMatrix;
	Matrix3x3 localToWorldMatrix;

	void SetRect();
	void UpdateMatrix();
public:
	Transform();
	Vector2 GetPosition();
	RECT GetRect(){ return rect; };
	Vector2 GetScale();
	float GetRotation() { return rotation; };
	Vector2 GetAnchorPoint();
	Vector2 GetWorldPosition();
	Matrix3x3 GetLocalToWorldMatrix();
	Matrix3x3 GetScaleMatrix();
	Matrix3x3 GetTranslateMatrix();
	Matrix3x3 GetRotateMatrix();

	void SetPosition(Vector2 _position);
	void SetAnchorPoint(Vector2 anchorPoint);
	void SetRotation(float rotation) { this->rotation = rotation; };
	void SetScale(Vector2 scale);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetSize(D2D1_RECT_F size) { this->size = size; };
	void SetRect(RECT rect);
	void SetWorldPosition(Vector2 position);

	void Translate(Vector2 delta);

	void SetDepth(int depth) { this->depth = depth; }
	int GetDepth() { return depth; }

	virtual void Init() override;
	virtual void Update() override;
};

