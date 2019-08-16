#pragma once
#include "SFML\Graphics.hpp"
#include <math.h>

using namespace sf;

class MathHelper
{
public:

	static float Dot(const Vector2f& v1, const Vector2f& v2);
	static float Magnitude(const Vector2f& v);
	static Vector2f Normalized(const Vector2f& v);
	static bool AlmostZero(float value, float threshold = 0.001f);
};

