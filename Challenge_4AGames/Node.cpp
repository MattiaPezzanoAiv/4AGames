#include "Node.h"
//#include <algorithm>
#include <functional>

Node::Node(int x, int y)
{
	gridPosition.x = x;
	gridPosition.y = y;
}

void Node::AddNeighbour(Node * node)
{
	this->neighbours.push_back(node);
}

sf::Vector2f Node::GridToScreenPos(float cellW, float cellH) const
{
	return sf::Vector2f(gridPosition.x * cellW, gridPosition.y * cellH);
}
