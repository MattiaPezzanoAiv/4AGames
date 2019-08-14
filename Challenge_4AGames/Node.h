#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

class Node
{
public:
	Node(int x, int y);
	~Node();

	void AddNeighbour(Node* node);

	std::vector<Node*> neighbours;
	sf::Vector2f GridToScreenPos(float cellW, float cellH);
private:
	sf::Vector2i gridPosition;
};

