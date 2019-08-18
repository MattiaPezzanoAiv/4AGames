#include "gtest\gtest.h"
#include "../Challenge_4AGames/Bullet.h"

TEST(Bullet, Movements) {

	Bullet b(sf::Vector2f(), sf::Vector2f(1,0), 100, 0, 0);
	auto pos = b.SimulateMove(1);
	
	EXPECT_FLOAT_EQ(pos.x, 100);
	EXPECT_FLOAT_EQ(pos.y, 0);
}
TEST(Bullet, MovementsOffset) {

	Bullet b(sf::Vector2f(50,50), sf::Vector2f(1, 1), 200, 0, 0);
	auto pos = b.SimulateMove(1);

	EXPECT_FLOAT_EQ(pos.x, 250);
	EXPECT_FLOAT_EQ(pos.y, 250);
}
TEST(Bullet, MovementsZero) {

	Bullet b(sf::Vector2f(50,50), sf::Vector2f(1, 1), 0, 0, 0);
	auto pos = b.SimulateMove(2.5f);

	EXPECT_FLOAT_EQ(pos.x, 50);
	EXPECT_FLOAT_EQ(pos.y, 50);
}
TEST(Bullet, MovementsFloat) {

	Bullet b(sf::Vector2f(50, 50), sf::Vector2f(0.5f, 0.5f), 50, 0, 0);
	auto pos = b.SimulateMove(2.5f);

	EXPECT_FLOAT_EQ(pos.x, 112.5f);
	EXPECT_FLOAT_EQ(pos.y, 112.5f);
}

TEST(Bullet, DeathTimeOk) {

	Bullet b(sf::Vector2f(50, 50), sf::Vector2f(0.5f, 0.5f), 50, 10.5f, 3.0f);
	auto dTime = b.GetDeathTime();

	EXPECT_FLOAT_EQ(dTime, 13.5f);
}
TEST(Bullet, DeathTimeZero) {

	Bullet b(sf::Vector2f(50, 50), sf::Vector2f(0.5f, 0.5f), 50, 0, 0);
	auto dTime = b.GetDeathTime();

	EXPECT_FLOAT_EQ(dTime, 0);
}