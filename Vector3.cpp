#include "stdafx.h"
#include "GgaetIp.h"

const Vector3 Vector3::forword = Vector3(0, 0, 1);
const Vector3 Vector3::right = Vector3(1, 0, 0);
const Vector3 Vector3::left = Vector3(-1, 0, 0);
const Vector3 Vector3::back = Vector3(0, 0, -1);
const Vector3 Vector3::up = Vector3(0, 1, 0);
const Vector3 Vector3::down = Vector3(0, -1, 0);
const Vector3 Vector3::zero = Vector3(0, 0, 0);

bool Vector3::operator==(const Vector3& right)
{
	return (x == right.x) && (y == right.y) && (z == right.z);
}

Vector3 Vector3::operator-(const Vector3&  right)
{
	return Vector3(x - right.x, y - right.y,z - right.z);
}

Vector3 Vector3::operator+(const Vector3&  right)
{
	return Vector3(x + right.x, y + right.y, z + right.z);
}

void Vector3::operator+=(const Vector3&  right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
}

void Vector3::operator-=(const Vector3&  right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
}

Vector3 Vector3::operator*(float right)
{
	return Vector3(x * right, y * right, z*right);
}

Vector3 Vector3::operator/(int right)
{
	return Vector3(x / right, y / right, z / right);
}

Vector3 Vector3::operator*(const Vector3& right)
{
	return Vector3(x * right.x, y * right.y, z * right.z);
}


Vector3 Vector3::operator/(const Vector3& right)
{
	return Vector3(x / right.x, y / right.y, z / right.z);
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float i)
{
	float x = (1 - i)*a.x  + i * b.x ;
	float y = (1 - i)*a.y  + i * b.y ;
	float z = (1 - i)*a.z + i * b.z;

	return Vector3(x, y, z);
}

void Vector3::Swap(Vector3* a, Vector3* b)
{
	Vector3 temp = *a;
	*a = *b;
	*b = temp;
}

float Vector3::SqrMagnitude()
{
	float xy = sqrt(pow(x, 2) + pow(y, 2));
	return pow(z,2)+pow(xy,2);
}

float Vector3::Magnitude()
{
	return sqrt(SqrMagnitude());
}

Vector3 Vector3::Normalize()
{
	return Vector3(x, y, z) / Magnitude();
}

float Vector3::Dot(Vector3 a, Vector3 b)
{
	return a.x  * b.x  + a.y  * b.y  + a.z * b.z;
}

Vector3 Vector3::Rotate(float rotation,Vector3 axis)
{
	Vector3 v = Vector3(x, y, z);
	Vector3 vRot = v*cos(rotation*Deg2Rad) + axis * (Vector3::Dot(axis, v))*(1 - cos(rotation*Deg2Rad)) + Vector3::Cross(axis, v)*sin(rotation*Deg2Rad);
	return vRot;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
	float x = a.y *b.z - a.z*b.y ;
	float y = a.y *b.x  - a.x *b.y ;
	float z = a.x *b.z - a.z*b.x ;
	return Vector3(x,y,z);
}