#include "stdafx.h"
#include "Segment.h"

class MathHelper;

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
	return MathHelper::Magnitude(p1 - p2);
}

Vector2f Segment::GetNormal() const
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	return MathHelper::Normalized(Vector2f(-dy, dx));
}

Vector2f Segment::Reflect(const Vector2f& vectorDir) const
{
	sf::Vector2f normal = GetNormal();
	//check if I have to flip the normal
	float dirDotNormal = MathHelper::Dot(vectorDir, normal);
	if (dirDotNormal >= 0)
		normal *= -1.0f;	//flip normal

	Vector2f reflectedVector;
	Vector2f dir(vectorDir);
	float dotMulTwo = 2 * MathHelper::Dot(vectorDir, normal);
	if (!MathHelper::AlmostZero(dotMulTwo))	//almost parallel
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
	sf::Vector2f ab = MathHelper::Normalized(p2 - p1);
	sf::Vector2f ah = MathHelper::Dot(ac, ab) * ab;

	float acLen = MathHelper::Magnitude(ac);
	float ahLen = MathHelper::Magnitude(ah);
	return ((acLen * acLen) - (ahLen * ahLen)) <= r2;*/

	/*sf::Vector2f ac = other.GetPosition() - p1;
	sf::Vector2f ab = MathHelper::Normalized(p2 - p1);
	sf::Vector2f ah = MathHelper::Dot(ac, ab) * ab;
	sf::Vector2f h = p1 + ah;
	return MathHelper::Magnitude(h - other.GetPosition()) <= BULLET_RADIUS;*/

	/*sf::Vector2f ac = other.GetPosition() - p1;
	sf::Vector2f ab = MathHelper::Normalized(p2 - p1);
	sf::Vector2f ah = ab * MathHelper::Dot(ac, ab);
	sf::Vector2f h = p1 + ah;
	return MathHelper::Magnitude(h - other.GetPosition()) <= BULLET_RADIUS;*/

	float p1Dist = MathHelper::Magnitude(this->p1 - other.GetPosition());
	float p2Dist = MathHelper::Magnitude(this->p2 - other.GetPosition());
	return (p1Dist + p2Dist - this->GetLength()) <= BULLET_RADIUS;	//this should work
}

bool Segment::Intersect(const Vector2f & otherP1, const Vector2f & otherP2, Vector2f * const intersectionPointPtr) const
{
	// Denominator for ua and ub are the same, so store this calculation
	float d = (otherP2.y - otherP1.y) * (p2.x - p1.x) - (otherP2.x - otherP1.x) * (p2.y - p1.y);

	//n_a and n_b are calculated as seperate values for readability
	float n_a = (otherP2.x - otherP1.x) * (p1.y - otherP1.y) - (otherP2.y - otherP1.y) * (p1.x - otherP1.x);

	float n_b = (p2.x - p1.x) * (p1.y - otherP1.y) - (p2.y - p1.y) * (p1.x - otherP1.x);

	// Make sure there is not a division by zero - this also indicates that
	// the lines are parallel.
	// If n_a and n_b were both equal to zero the lines would be on top of each
	// other (coincidental).  This check is not done because it is not
	// necessary for this implementation (the parallel check accounts for this).
	if (d == 0)
		return false;

	// Calculate the intermediate fractional point that the lines potentially intersect.
	float ua = n_a / d;
	float ub = n_b / d;

	// The fractional point will be between 0 and 1 inclusive if the lines
	// intersect.  If the fractional calculation is larger than 1 or smaller
	// than 0 the lines would need to be longer to intersect.
	if (ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0)
	{
		if (intersectionPointPtr != nullptr)
		{
			intersectionPointPtr->x = p1.x + (ua * (p2.x - p1.x));
			intersectionPointPtr->y = p1.y + (ua * (p2.y - p1.y));
		}
		return true;
	}
	return false;
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

