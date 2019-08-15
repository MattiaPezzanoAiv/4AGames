#pragma once
#include "Node.h"
#include <iostream>
#include <stack>
#include "BulletManager.h"
#include "Segment.h"

class Grid
{
public:
	Grid(int width,int height);
	~Grid();
	Grid(const Grid& copy) = delete;	//disable copy

	void DistributeSegments(BulletManager* const bManager);
	int BidimensionalToIndex(int row, int col) const;

private:
	int rows, cols;
	std::vector<Node*> nodes;
	float cellW, cellH;

};

