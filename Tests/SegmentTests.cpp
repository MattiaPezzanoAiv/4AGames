#include "gtest\gtest.h"
#include "../Challenge_4AGames/segment.h"

TEST(Segment, Normal) {

	Segment seg(sf::Vector2f(0, 1), sf::Vector2f(0, 0));
	auto normal = seg.GetNormal();

	EXPECT_FLOAT_EQ(normal.x, 1);
	EXPECT_FLOAT_EQ(normal.y, 0);
}
TEST(Segment, NormalReversed) {

	Segment seg(sf::Vector2f(0, 0), sf::Vector2f(0, 1));
	auto normal = seg.GetNormal();

	EXPECT_FLOAT_EQ(normal.x, -1);
	EXPECT_FLOAT_EQ(normal.y, 0);
}
TEST(Segment, Reflect) {

	Segment seg(sf::Vector2f(0, 0), sf::Vector2f(0, 1));
	auto reflected = seg.Reflect(sf::Vector2f(-1, 0));

	EXPECT_FLOAT_EQ(reflected.x, 1);
	EXPECT_FLOAT_EQ(reflected.y, 0);
}
TEST(Segment, ReflectReversed) {

	Segment seg(sf::Vector2f(0, 0), sf::Vector2f(0, 1));
	auto reflected = seg.Reflect(sf::Vector2f(1, 0));

	EXPECT_FLOAT_EQ(reflected.x, -1);
	EXPECT_FLOAT_EQ(reflected.y, 0);
}
TEST(Segment, ReflectNot90) {

	Segment seg(sf::Vector2f(0, 0), sf::Vector2f(0, 1));
	auto reflected = seg.Reflect(sf::Vector2f(-0.5f, -0.5f));

	EXPECT_FLOAT_EQ(reflected.x, 0.5f);
	EXPECT_FLOAT_EQ(reflected.y, -0.5f);
}



//intersection
TEST(Segment, IntersectionTrue) {

	Segment seg(sf::Vector2f(1, 0), sf::Vector2f(1, 2));

	//simulate bullet projection
	sf::Vector2f startPos(0, 1);
	sf::Vector2f endPos(2, 1);

	bool intersect = seg.Intersect(startPos, endPos, nullptr);

	EXPECT_TRUE(intersect);
}
TEST(Segment, IntersectionFalse) {

	Segment seg(sf::Vector2f(10, 4), sf::Vector2f(8, 4));

	//simulate bullet projection
	sf::Vector2f startPos(0, 1);
	sf::Vector2f endPos(2, 1);

	bool intersect = seg.Intersect(startPos, endPos, nullptr);

	EXPECT_FALSE(intersect);
}
TEST(Segment, IntersectionPoint) {

	Segment seg(sf::Vector2f(1, 0), sf::Vector2f(1, 2));

	//simulate bullet projection
	sf::Vector2f startPos(0, 1);
	sf::Vector2f endPos(2, 1);
	sf::Vector2f intersectPoint(0, 0);

	bool intersect = seg.Intersect(startPos, endPos, &intersectPoint);

	EXPECT_TRUE(intersect);
	EXPECT_FLOAT_EQ(intersectPoint.x, 1);
	EXPECT_FLOAT_EQ(intersectPoint.y, 1);
}
TEST(Segment, IntersectionComplex) {

	Segment seg(sf::Vector2f(-5.0f, 0), sf::Vector2f(5.0f, 0));

	//simulate bullet projection
	sf::Vector2f startPos(1, -2);
	sf::Vector2f endPos(1, 2);
	sf::Vector2f intersectPoint(0, 0);

	bool intersect = seg.Intersect(startPos, endPos, &intersectPoint);

	EXPECT_TRUE(intersect);
	EXPECT_FLOAT_EQ(intersectPoint.x, 1);
	EXPECT_FLOAT_EQ(intersectPoint.y, 0);
}
TEST(Segment, IntersectionDiagonal) {

	Segment seg(sf::Vector2f(0,0), sf::Vector2f(10,10));

	//simulate bullet projection
	sf::Vector2f startPos(0,10);
	sf::Vector2f endPos(10, 0);
	sf::Vector2f intersectPoint(0, 0);

	bool intersect = seg.Intersect(startPos, endPos, &intersectPoint);

	EXPECT_TRUE(intersect);
	EXPECT_FLOAT_EQ(intersectPoint.x, 5);
	EXPECT_FLOAT_EQ(intersectPoint.y, 5);
}
