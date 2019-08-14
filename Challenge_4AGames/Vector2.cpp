#include "stdafx.h"
#include "Vector2.h"

Vector2::Vector2()
{//a
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2 & copy)
{
	this->x = copy.x;
	this->y = copy.y;
}


Vector2::~Vector2()
{
}

Vector2 & Vector2::operator+=(const Vector2 other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2 other)
{
	Vector2 v = Vector2(*this);
	v += other;
	return v;
}

Vector2 Vector2::operator-(const Vector2 other)
{
	Vector2 v = Vector2(*this);
	v -= other;
	return v;
}

Vector2 & Vector2::operator-=(const Vector2 other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator*(const float scalar)
{
	Vector2 v = Vector2(*this);
	v *= scalar;
	return v;
}

Vector2 & Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 Vector2::operator*(const int scalar)
{
	Vector2 v = Vector2(*this);
	v *= scalar;
	return v;
}

Vector2 & Vector2::operator*=(const int scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

bool Vector2::operator==(const Vector2 other)
{
	return fabs(x - other.x) < EPSILON && fabs(y - other.y) < EPSILON;
}

bool Vector2::operator!=(const Vector2 other)
{
	return !(*this == other);
}

float Vector2::Magnitude()
{
	return sqrt(FastMagnitude());
}

float Vector2::FastMagnitude()
{
	return (x * x + y * y);
}

Vector2 Vector2::Normalized()
{
	float len = Magnitude();
	return Vector2(x / len, y / len);
}

void Vector2::Normalize()
{
	float len = Magnitude();
	x /= len;
	y /= len;
}

float Vector2::Dot(const Vector2 v1, const Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

