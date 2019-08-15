#pragma once
#include "SFML/Graphics.hpp"
#include "VectorHelper.h"
#include "Bullet.h"
#include "Defines.h"
#include <math.h>
#include <iostream>

using namespace sf;

class Segment
{
public:
	Segment(Vector2f p1, Vector2f p2);

	float GetLength() const;
	Vector2f GetNormal() const;
	Vector2f Reflect(const Vector2f& vectorDir) const;

	//this method returns true if there is an intersection, otherwise returns false.
	bool Intersect(const Bullet& other) const;
	
	void Render(RenderWindow* const windowPtr) const;

	sf::VertexArray line;

	sf::Vector2f GetPoint(int idx) const;

private:
	Vector2f p1, p2;
	bool AlmostZero(float value, float threshold = 0.001f) const;
};

