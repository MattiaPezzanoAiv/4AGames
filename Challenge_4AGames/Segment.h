#pragma once
#include "MathHelper.h"
#include "Bullet.h"
#include "Defines.h"
#include <math.h>

using namespace sf;

class Segment
{
public:
	Segment(Vector2f p1, Vector2f p2);

	float GetLength() const;
	Vector2f GetNormal() const;
	Vector2f Reflect(const Vector2f& vectorDir) const;

	//this method returns true if there is an intersection, otherwise returns false.
	//if there is a collision the intersection point will be stored in the intersectionPoint variable.
	//If you don't want the result can pass nullptr.
	bool Intersect(const Vector2f& otherP1, const Vector2f& otherP2, Vector2f* const intersectionPoint) const;
	
	void Render(RenderWindow* const windowPtr) const;


	sf::Vector2f GetPoint(int idx) const;

private:
	sf::VertexArray line;
	Vector2f p1, p2;
};

