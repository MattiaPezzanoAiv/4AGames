#include "stdafx.h"
#include "VectorHelper.h"

float VectorHelper::Dot(const Vector2f & v1, const Vector2f & v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float VectorHelper::Magnitude(const Vector2f & v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f VectorHelper::Normalized(const Vector2f & v)
{
	float len = VectorHelper::Magnitude(v);
	Vector2f result(0,0);
	if (len > 0)
	{
		result.x = v.x / len;
		result.y = v.y / len;
	}
	return result;
}