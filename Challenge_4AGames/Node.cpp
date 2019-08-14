#include "stdafx.h"
#include "Node.h"


Node::Node(int x, int y)
{
	gridPosition.x = x;
	gridPosition.y = y;
}


Node::~Node()
{
}

void Node::AddNeighbour(Node * node)
{
	this->neighbours.push_back(node);
}

sf::Vector2f Node::GridToScreenPos(float cellW, float cellH)
{
	return sf::Vector2f(gridPosition.x * cellW, gridPosition.y * cellH);
}
