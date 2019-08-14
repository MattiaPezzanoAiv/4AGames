#include "stdafx.h"
#include "Grid.h"

//needed for ptrs
class Node;
class BulletManager;
class Segment;

Grid::Grid(const int rows, const int cols, const float cellWidth, const float cellHeight)
{
	this->rows = rows;
	this->cols = cols;
	this->cellW = cellWidth;
	this->cellH = cellHeight;

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			//fill with nodes
			Node* node = new Node(j, i);
			nodes.push_back(node);
		}
	}

	//add neighbours
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			Node* node = this->nodes[this->BidimensionalToIndex(j,i)];
			if (i > 0) {     // has north
				node->AddNeighbour(this->nodes[this->BidimensionalToIndex(i -1, j)]);
			}
			if (i < rows - 1) { // has south
				node->AddNeighbour(this->nodes[this->BidimensionalToIndex(i + 1, j)]);
			}
			if (j > 0) {     // hast
				node->AddNeighbour(this->nodes[this->BidimensionalToIndex(i, j-1)]);
			}
			if (j < cols - 1) { // east
				node->AddNeighbour(this->nodes[this->BidimensionalToIndex(i, j+1)]);
			}
		}
	}

	
}

Grid::~Grid()
{
	std::cout << "count " << nodes.size() << std::endl;
	for (auto n : nodes)
	{
		delete n;

	}
}

void Grid::DistributeSegments(BulletManager * const bManager)
{
	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			if (j > 0)
			{
				int idx1 = BidimensionalToIndex(j, i);
				int idx2 = BidimensionalToIndex(j - 1, i);

				sf::Vector2f p1(nodes[idx1]->GridToScreenPos(cellW, cellH));
				sf::Vector2f p2(nodes[idx2]->GridToScreenPos(cellW, cellH));
				Segment* seg = new Segment(p1, p2);
				bManager->AddWall(seg);
			}
			if (i > 0)
			{
				int idx1 = BidimensionalToIndex(j, i);
				int idx2 = BidimensionalToIndex(j, i - 1);

				sf::Vector2f p1(nodes[idx1]->GridToScreenPos(cellW, cellH));
				sf::Vector2f p2(nodes[idx2]->GridToScreenPos(cellW, cellH));
				Segment* seg = new Segment(p1, p2);
				bManager->AddWall(seg);
			}
		}
	}
}

int Grid::BidimensionalToIndex(int row, int col) const
{
	return (row * cols) + col;
}

