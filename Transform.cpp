#include "stdafx.h"
#include "GgaetIp.h"
#include <typeinfo>

Transform::Transform()
{
	anchorPoint = Vector2(0.5f, 0.5f);
	position = Vector2::zero;
	scale = Vector2(1, 1);

	scaleMatrix = Matrix3x3::identity;
	rotateMatrix = Matrix3x3::identity;
	translateMatrix = Matrix3x3::identity;
	localToWorldMatrix = Matrix3x3::identity;
}

void Transform::Translate(Vector2 delta)
{
	position.x = position.x +delta.x;
	position.y = position.y  - delta.y;
}

Vector2 Transform::GetPosition()
{
	return Vector2(position.x ,-position.y );
}

Vector2 Transform::GetScale()
{
	return scale;
};

void Transform::SetPosition(Vector2 _position)
{
	position = Vector2(_position.x , -_position.y );
};

void Transform::SetWorldPosition(Vector2 _position)
{
	Object* parent = object->GetParent();
	Vector2 minusPosition = Vector2::zero;

	while (parent != nullptr)
	{
		minusPosition += parent->GetTransform()->GetPosition();
		parent = parent->GetParent();
	}
	position =_position - minusPosition;
};

void Transform::SetAnchorPoint(Vector2 anchorPoint)
{
	this->anchorPoint = anchorPoint;
};

void Transform::SetScale(Vector2 scale)
{
	this->scale = scale;
};

void Transform::SetScaleX(float x)
{
	scale.x = x;
};

Matrix3x3 Transform::GetLocalToWorldMatrix()
{
	return localToWorldMatrix;
}
Matrix3x3 Transform::GetScaleMatrix()
{
	return scaleMatrix;
}
Matrix3x3 Transform::GetTranslateMatrix()
{
	return translateMatrix;
}
Matrix3x3 Transform::GetRotateMatrix()
{
	return rotateMatrix;
}
;

void Transform::SetScaleY(float y)
{
	scale.y = y;
};

Vector2 Transform::GetAnchorPoint()
{
	return anchorPoint;
};

void Transform::Init()
{
	SetRect();
	UpdateMatrix();
}

Vector2 Transform::GetWorldPosition()
{
	return Vector2(localToWorldMatrix.m[2][0], localToWorldMatrix.m[2][1]);
}


void Transform::SetRect()
{
	float width = size.right - size.left;
	float height = size.bottom - size.top;

	rect.left = -(width * anchorPoint.x );
	rect.top = -(height * anchorPoint.y );
	rect.right = (width * (1-anchorPoint.x ));
	rect.bottom = (height * (1-anchorPoint.y ));
}

void Transform::Update()
{
	SetRect();
	UpdateMatrix();
}

void Transform::SetRect(RECT rect)
{
	this->rect = rect;
	float width = size.right - size.left;
	float height = size.bottom - size.top;

	position.x = rect.left + (width*anchorPoint.x );
	position.y = rect.bottom - (height*anchorPoint.y );
}

void Transform::UpdateMatrix()
{
	scaleMatrix.m[0][0] = scale.x ;
	scaleMatrix.m[1][1] = scale.y ;

	rotateMatrix.m[0][0] = cos(rotation*Deg2Rad);
	rotateMatrix.m[0][1] = -sin(rotation*Deg2Rad);
	rotateMatrix.m[1][0] = sin(rotation*Deg2Rad);
	rotateMatrix.m[1][1] = cos(rotation*Deg2Rad);

	translateMatrix.m[2][0] = position.x ;
	translateMatrix.m[2][1] = position.y ;

	localToWorldMatrix = scaleMatrix * rotateMatrix * translateMatrix;

	Object* parent = object->GetParent();
	if (!parent)
		return;
	localToWorldMatrix = localToWorldMatrix * parent->GetTransform()->GetLocalToWorldMatrix();
}
