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

	sf::Vector2f GetScreenPos(const Node* const node) const;

	//distribute walls on a standard grid
	void DistributeSegments(BulletManager* const bManager);
	
	//transform a bidimensional coordinate to a monodimensional one. used to access nodes vector.
	int BidimensionalToIndex(int row, int col) const;

private:
	unsigned int rows, cols;
	std::vector<Node*> nodes;
	float cellW, cellH;

};

