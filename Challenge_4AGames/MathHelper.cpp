#include "MathHelper.h"

float MathHelper::Dot(const Vector2f & v1, const Vector2f & v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float MathHelper::Magnitude(const Vector2f & v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f MathHelper::Normalized(const Vector2f & v)
{
	float len = MathHelper::Magnitude(v);
	Vector2f result(0,0);
	if (len > 0)
	{
		result.x = v.x / len;
		result.y = v.y / len;
	}
	return result;
}

bool MathHelper::AlmostZero(float value, float threshold)
{
	return value < threshold && value > -threshold;
}