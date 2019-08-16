#include "gtest\gtest.h"
#include "../Challenge_4AGames/MathHelper.h"

//magnitude func
TEST(MathHelper, MagnitudeUnit) {

	sf::Vector2f v1(0,1);
	float len = MathHelper::Magnitude(v1);

	EXPECT_FLOAT_EQ(len, 1);
}
TEST(MathHelper, Magnitude) {

	sf::Vector2f v1(0, 4);
	float len = MathHelper::Magnitude(v1);

	EXPECT_FLOAT_EQ(len, 4); 
}
TEST(MathHelper, Magnitude2) {

	sf::Vector2f v1(10, 10);
	float len = MathHelper::Magnitude(v1);

	EXPECT_FLOAT_EQ(len, 14.1421356f);
}
TEST(MathHelper, MagnitudeNegative) {

	sf::Vector2f v1(2.5f, 0);
	float len = MathHelper::Magnitude(v1);

	EXPECT_FLOAT_EQ(len, 2.5f);
}
TEST(MathHelper, MagnitudeZero) {

	sf::Vector2f v1(0, 0);
	float len = MathHelper::Magnitude(v1);

	EXPECT_FLOAT_EQ(len, 0);
}



//normalized func
TEST(MathHelper, NormalizedLen) {

	sf::Vector2f v1(20, 50.3f);
	sf::Vector2f norm = MathHelper::Normalized(v1);

	EXPECT_FLOAT_EQ(MathHelper::Magnitude(norm), 1);
}
TEST(MathHelper, NormalizedLenNegative) {

	sf::Vector2f v1(-10, 50.3f);
	sf::Vector2f norm = MathHelper::Normalized(v1);

	EXPECT_FLOAT_EQ(MathHelper::Magnitude(norm), 1);
}
TEST(MathHelper, NormalizedLenZero) {

	sf::Vector2f v1(0,0);
	sf::Vector2f norm = MathHelper::Normalized(v1);

	EXPECT_FLOAT_EQ(MathHelper::Magnitude(norm), 0);
}
TEST(MathHelper, NormalizedVal) {

	sf::Vector2f v1(50, 0);
	sf::Vector2f norm = MathHelper::Normalized(v1);

	EXPECT_FLOAT_EQ(norm.x, 1);
	EXPECT_FLOAT_EQ(norm.y, 0);
}
TEST(MathHelper, NormalizedVal2) {

	sf::Vector2f v1(0, -2);
	sf::Vector2f norm = MathHelper::Normalized(v1);

	EXPECT_FLOAT_EQ(norm.x, 0);
	EXPECT_FLOAT_EQ(norm.y, -1);
}





//dot func
TEST(MathHelper, DotEqual) {

	sf::Vector2f v1(0, 1);
	float dot = MathHelper::Dot(v1, v1);

	EXPECT_FLOAT_EQ(dot, 1);
}
TEST(MathHelper, DotZero) {

	sf::Vector2f v1(0, 0);
	float dot = MathHelper::Dot(v1, v1);

	EXPECT_FLOAT_EQ(dot, 0);
}
TEST(MathHelper, DotOpposite) {

	sf::Vector2f v1(1, 0);
	sf::Vector2f v2(-1, 0);
	float dot = MathHelper::Dot(v1, v2);

	EXPECT_FLOAT_EQ(dot, -1);
}
TEST(MathHelper, DotNegative) {

	sf::Vector2f v1(-1, 0);
	float dot = MathHelper::Dot(v1, v1);

	EXPECT_FLOAT_EQ(dot, 1);
}
TEST(MathHelper, DotAllOne) {

	sf::Vector2f v1(1, 1);
	float dot = MathHelper::Dot(v1, v1);

	EXPECT_FLOAT_EQ(dot, 2);
}
TEST(MathHelper, DotOpposite2) {

	sf::Vector2f v1(1, 1);
	sf::Vector2f v2(-1, -1);
	float dot = MathHelper::Dot(v1, v2);

	EXPECT_FLOAT_EQ(dot, -2);
}


//almost zero
TEST(MathHelper, NotAlmostZero) {

	float treshold = 0.000001f;
	bool result = MathHelper::AlmostZero(0.12f, treshold);

	EXPECT_FALSE(result);
}
TEST(MathHelper, NotAlmostZeroNegative) {

	float treshold = 0.000001f;
	bool result = MathHelper::AlmostZero(-0.02f, treshold);

	EXPECT_FALSE(result);
}
TEST(MathHelper, AlmostZero) {

	float treshold = 0.00001f;
	bool result = MathHelper::AlmostZero(0.000001f, treshold);

	EXPECT_TRUE(result);
}
TEST(MathHelper, AlmostZeroNegative) {

	float treshold = 0.00001f;
	bool result = MathHelper::AlmostZero(-0.000001f, treshold);

	EXPECT_TRUE(result);
}
TEST(MathHelper, AlmostZeroWithZero) {

	float treshold = 0.00001f;
	bool result = MathHelper::AlmostZero(0, treshold);

	EXPECT_TRUE(result);
}