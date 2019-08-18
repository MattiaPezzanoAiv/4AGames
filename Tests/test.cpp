#include "gtest\gtest.h"
#include "../Challenge_4AGames/BulletManager.h"


TEST(Global, StepCollisionTest)
{
	BulletManager manager;
	manager.Fire(sf::Vector2f(100, 0), sf::Vector2f(1, 0), 100, 0, 5000);

	Segment w1(sf::Vector2f(0, -50), sf::Vector2f(0, 50));
	Segment w2(sf::Vector2f(200, -50), sf::Vector2f(200, 50));
	manager.AddWall(std::move(w1));
	manager.AddWall(std::move(w2));

	/*
	situation:
	|		|
	|		|
	|	* ->|
	|		|
	|		|

	equal distance from the 2 walls
	after 4 seconds I expect the same point as start
	
	*/

	manager.SyncWriteToReadBuffer();
	Bullet& bullet = manager.GetBullet(0);
	
	manager.Update(4);

	EXPECT_FLOAT_EQ(bullet.GetPosition().x, 100);
	EXPECT_FLOAT_EQ(bullet.GetPosition().y, 0);
}
TEST(Global, StepCollisionTestRedLight)
{
	BulletManager manager;
	manager.Fire(sf::Vector2f(100, 0), sf::Vector2f(1, 0), 100, 0, 5000);

	Segment w1(sf::Vector2f(0, -50), sf::Vector2f(0, 50));
	Segment w2(sf::Vector2f(200, -50), sf::Vector2f(200, 50));
	manager.AddWall(std::move(w1));
	manager.AddWall(std::move(w2));

	/*
	situation:
	|		|
	|		|
	|	* ->|
	|		|
	|		|

	equal distance from the 2 walls
	after 4 seconds I expect the same point as start

	*/

	manager.SyncWriteToReadBuffer();
	Bullet& bullet = manager.GetBullet(0);

	manager.Update(3);	//don't use two. is valid as the test above

	EXPECT_TRUE(bullet.GetPosition().x != 100);
	EXPECT_FLOAT_EQ(bullet.GetPosition().y, 0);
}

TEST(Global, WriteBufferBlit)
{
	BulletManager manager;

	EXPECT_EQ(manager.GetBulletCount(), 0);
	manager.Fire(sf::Vector2f(100, 0), sf::Vector2f(1, 0), 100, 0, 5000);
	EXPECT_EQ(manager.GetBulletCount(), 0);
	manager.SyncWriteToReadBuffer();
	EXPECT_EQ(manager.GetBulletCount(), 1);
}
TEST(Global, WriteBufferNoBlit)
{
	BulletManager manager;

	EXPECT_EQ(manager.GetBulletCount(), 0);
	manager.Fire(sf::Vector2f(100, 0), sf::Vector2f(1, 0), 100, 0, 5000);
	EXPECT_EQ(manager.GetBulletCount(), 0);
	EXPECT_EQ(manager.GetBulletCount(), 0);
}

int main(int argc, char** args)
{
	::testing::InitGoogleTest(&argc, args);
	RUN_ALL_TESTS();
	system("pause");
}