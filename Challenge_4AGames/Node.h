#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

class Node
{
public:
	Node(int x, int y);

	void AddNeighbour(Node* node);
	sf::Vector2f GridToScreenPos(float cellW, float cellH) const;

	bool IsVisited;

private:
	std::vector<Node*> neighbours;
	sf::Vector2i gridPosition;
};

