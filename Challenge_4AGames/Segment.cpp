#include "stdafx.h"
#include "Segment.h"

class VectorHelper;

Segment::Segment(Vector2f p1, Vector2f p2)
{
	this->p1 = p1;
	this->p2 = p2;

	this->line.setPrimitiveType(PrimitiveType::LinesStrip);
	this->line.append(Vertex(this->p1, WALL_COLOR));
	this->line.append(Vertex(this->p2, WALL_COLOR));
}

float Segment::GetLength() const
{
	return VectorHelper::Magnitude(p1 - p2);
}

Vector2f Segment::GetNormal() const
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	return VectorHelper::Normalized(Vector2f(-dy, dx));
}

Vector2f Segment::Reflect(const Vector2f& vectorDir) const
{
	sf::Vector2f normal = GetNormal();
	//check if I have to flip the normal
	float dirDotNormal = VectorHelper::Dot(vectorDir, normal);
	if (dirDotNormal >= 0)
		normal *= -1.0f;	//flip normal

	Vector2f reflectedVector;
	Vector2f dir(vectorDir);
	float dotMulTwo = 2 * VectorHelper::Dot(vectorDir, normal);
	if (!AlmostZero(dotMulTwo))	//almost parallel
	{
		/*
		handles this

		° A
		|
		|
		|
		° B
		
		^ dir 
		| 
		|
		|
		
		this should reflect in the opposite way
		*/
		reflectedVector = normal * dotMulTwo;
		reflectedVector = dir - reflectedVector;
	}
	else
		reflectedVector = dir * -1.0f;
	
	return reflectedVector;
}

bool Segment::Intersect(const Bullet & other) const
{
	/*sf::Vector2f ac = other.GetPosition() - p1;
	float r2 = BULLET_RADIUS * BULLET_RADIUS;
	sf::Vector2f ab = VectorHelper::Normalized(p2 - p1);
	sf::Vector2f ah = VectorHelper::Dot(ac, ab) * ab;

	float acLen = VectorHelper::Magnitude(ac);
	float ahLen = VectorHelper::Magnitude(ah);
	return ((acLen * acLen) - (ahLen * ahLen)) <= r2;*/

	/*sf::Vector2f ac = other.GetPosition() - p1;
	sf::Vector2f ab = VectorHelper::Normalized(p2 - p1);
	sf::Vector2f ah = VectorHelper::Dot(ac, ab) * ab;
	sf::Vector2f h = p1 + ah;
	return VectorHelper::Magnitude(h - other.GetPosition()) <= BULLET_RADIUS;*/

	float p1Dist = VectorHelper::Magnitude(this->p1 - other.GetPosition());
	float p2Dist = VectorHelper::Magnitude(this->p2 - other.GetPosition());
	return (p1Dist + p2Dist - this->GetLength()) <= BULLET_RADIUS;	//this should work
}

void Segment::Render(RenderWindow* const windowPtr) const
{
	windowPtr->draw(line);
}

sf::Vector2f Segment::GetPoint(int idx) const
{
	if (idx < 0 || idx > 1)
		return sf::Vector2f();
	if (idx == 0)
		return p1;
	else
		return p2;
}

bool Segment::AlmostZero(float value, float threshold) const
{
	return value < threshold && value > -threshold;
}
