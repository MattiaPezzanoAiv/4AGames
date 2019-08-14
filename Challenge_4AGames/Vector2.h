#pragma once
#include <math.h>
#define EPSILON 0.000001f

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& copy);
	~Vector2();

	float x, y;


	Vector2& operator += (const Vector2 other);
	Vector2 operator + (const Vector2 other);

	Vector2 operator - (const Vector2 other);
	Vector2& operator -= (const Vector2 other);

	Vector2 operator * (const float scalar);
	Vector2& operator *= (const float scalar);

	Vector2 operator * (const int scalar);
	Vector2& operator *= (const int scalar);

	//the comparer takes care about float approximation
	bool operator == (const Vector2 other);
	bool operator != (const Vector2 other);

	float Magnitude();
	float FastMagnitude();
	Vector2 Normalized();
	void Normalize();	//normalize this vector (lose the current state)

	static float Dot(const Vector2 v1, const Vector2 v2);

};

