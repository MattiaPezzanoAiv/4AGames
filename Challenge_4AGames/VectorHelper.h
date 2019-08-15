#pragma once
#include "SFML\Graphics.hpp"
#include <math.h>

using namespace sf;

class VectorHelper
{
public:

	static float Dot(const Vector2f& v1, const Vector2f& v2);
	static float Magnitude(const Vector2f& v);
	static Vector2f Normalized(const Vector2f& v);
};

