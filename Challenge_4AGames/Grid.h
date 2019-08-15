#pragma once
#include "Node.h"
#include <iostream>
#include <stack>
#include "BulletManager.h"
#include "Segment.h"
#include <utility>

class Grid
{
public:
	Grid(unsigned int width,unsigned int height);
	~Grid();
	Grid(const Grid& copy) = delete;	//disable copy

	void DistributeSegments(BulletManager* const bManager);
	int BidimensionalToIndex(int row, int col) const;

private:
	unsigned int rows, cols;
	std::vector<Node*> nodes;
	float cellW, cellH;

};

