#pragma once

#include "SFML\Graphics.hpp"
#include "Defines.h"

using namespace sf;

class Bullet
{
public:
	Bullet(Vector2f pos, Vector2f dir, float speed, float spawnTime, float lifeTime);

	void Render(sf::RenderWindow* const windowPtr) const;
	//this method is responsible to sync the position etc, to the circle shape just before rendering
	void SetNewDirection(Vector2f newDir);
	
	//this method moves the bullet using the given direction and speed
	void Move(float deltaTime);

	float GetDeathTime() const;
	Vector2f GetPosition() const;
	Vector2f GetDirection() const;
	float GetSpawnTime() const;

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

