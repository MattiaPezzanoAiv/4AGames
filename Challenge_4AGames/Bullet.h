#pragma once

#include "SFML\Graphics.hpp"
#include "ActivableObject.h"
#include "Defines.h"

using namespace sf;

class Bullet : public ActivableObject
{
public:
	Bullet(Vector2f pos, Vector2f dir, float speed, float spawnTime, float lifeTime);
	~Bullet();

	void Render(sf::RenderWindow* const windowPtr) const;
	//this method is responsible to sync the position etc, to the circle shape just before rendering
	void SetNewDirection(Vector2f newDir);
	
	//this method moves the bullet using the given direction and speed
	void Move(float deltaTime);

	float GetDeathTime() const;
	Vector2f GetPosition() const;
	Vector2f GetDirection() const;
	float GetSpawnTime() const;

private:
	Vector2f position, direction;
	float speed, spawnTime, lifeTime;
	sf::CircleShape renderShape;
};

