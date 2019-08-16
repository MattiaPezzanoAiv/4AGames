#include "gtest\gtest.h"
#include "../Challenge_4AGames/Grid.h"

TEST(Grid, BidimToIdx) {

	Grid g(5, 5);
	int idx = g.BidimensionalToIndex(2, 2);

	EXPECT_EQ(idx, 12);
}
TEST(Grid, BidimToIdxZero) {

	Grid g(5, 5);
	int idx = g.BidimensionalToIndex(0, 0);

	EXPECT_EQ(idx, 0);
}
TEST(Grid, BidimToIdxNotZero) {

	Grid g(5, 5);
	int idx = g.BidimensionalToIndex(1, 0);

	EXPECT_TRUE(idx != 0);
}
TEST(Grid, BidimToIdxOne) {

	Grid g(5, 5);
	int idx = g.BidimensionalToIndex(1, 1);

	EXPECT_EQ(idx, 6);
}
TEST(Grid, BidimToIdxMax) {

	Grid g(5, 5);
	int idx = g.BidimensionalToIndex(4, 4);
	//zero based idxs. 5x5 -1

	EXPECT_EQ(idx, 24);
}