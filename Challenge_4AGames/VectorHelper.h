#pragma once
#include "SFML\Graphics.hpp"
#include <math.h>

using namespace sf;

class VectorHelper
{
public:
	VectorHelper();
	~VectorHelper();

	//return the dot product of two given vectors
	static float Dot(const Vector2f& v1, const Vector2f& v2);
	//return the length of the given vector
	static float Magnitude(const Vector2f& v);
	//return a new vector which is the normalized version of the given one
	static Vector2f Normalized(const Vector2f& v);
};

