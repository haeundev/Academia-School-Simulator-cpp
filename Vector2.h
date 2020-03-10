#pragma once
class Vector3;
class Vector2
{
public:
	Vector2() {};
	Vector2(float x, float y) : x(x), y(y) {};
	Vector2(POINT to) :x(to.x), y(to.y) {};
	float x;
	float y;

	static Vector2 Lerp(Vector2 a, Vector2 b, float i);
	static void Swap(Vector2* a, Vector2* b);
	static float Dot(Vector2 a, Vector2 b);
	static Vector3 Cross(Vector2 a, Vector2 b);

	Vector2 Normalize();
	float Magnitude();
	float SqrMagnitude();
	Vector2 Rotate(float rotation);

	static float GetAngle(Vector2 startPos, Vector2 endPos)
	{
		float x = startPos.x - endPos.x;
		float y = startPos.y - endPos.y;
		float angle = -atan2f(y, x);

		return angle;
	}

	static float GetDistance(Vector2 a, Vector2 b, bool check = true)
	{
		float x = b.x - a.x;
		float y = b.y - a.y;

		if (check)
			return sqrtf(x * x + y * y);
		else return x * x + y * y;
	}

	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 right;
	static const Vector2 left;
	static const Vector2 zero;

	Vector2 operator-(const Vector2& right);
	Vector2 operator+(const Vector2& right);
	Vector2 operator*(float right);
	Vector2 operator/(int right);
	Vector2 operator*(const Vector2& right);
	Vector2 operator/(const Vector2& right);
	void operator+=(const Vector2& right);
	void operator-=(const Vector2& right);
	bool operator==(const Vector2& right);
	bool operator!=(const Vector2& right);
	bool operator>=(const Vector2& right);
	bool operator<=(const Vector2& right);
	
	POINT Vec2ToPoint() { return POINT{ (int)this->x,(int)this->y }; }
};

