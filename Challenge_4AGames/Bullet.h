#pragma once
#include "SFML\Graphics.hpp"
#include "Defines.h"

using namespace sf;

class Bullet
{
public:
	Bullet(Vector2f pos, Vector2f dir, float speed, float spawnTime, float lifeTime);

	void Render(sf::RenderWindow* const windowPtr) const;
	
	void SetNewDirection(Vector2f newDir);
	
	//this returns the hypotetic final position simulated in the given delta time
	sf::Vector2f SimulateMove(float deltaTime) const;
	void SetPosition(sf::Vector2f pos);

	float GetDeathTime() const;
	Vector2f GetPosition() const;
	Vector2f GetDirection() const;
	float GetSpawnTime() const;
	float GetSpeed() const;

	bool IsActive() const
	{
		return isActive;
	}
	void SetActive(bool active)
	{
		isActive = active;
	}

private:
	Vector2f position, direction;
	float speed, spawnTime, lifeTime;
	sf::CircleShape renderShape;

	bool isActive = true;
};

