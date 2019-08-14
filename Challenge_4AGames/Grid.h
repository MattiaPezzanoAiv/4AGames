#pragma once
#include "Node.h"
#include <iostream>
#include <stack>
#include "BulletManager.h"
#include "Segment.h"

class Grid
{
public:
	Grid(const int width,const int height,const float cellWidth,const float cellHeight);
	~Grid();
	Grid(const Grid& copy) = delete;	//disable copy

	void DistributeSegments(BulletManager* const bManager);

private:
	float rows, cols;
	std::vector<Node*> nodes;
	int BidimensionalToIndex(int row, int col) const;
	float cellW, cellH;

};

