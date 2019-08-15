#include "pch.h"
#include "../Challenge_4AGames/Bullet.h"

TEST(Bullet, MoveGreen)
{
	Bullet bullet(sf::Vector2f(0,0), sf::Vector2f(1,0), 10, 0,0);

	bullet.Move(1.0f);

}