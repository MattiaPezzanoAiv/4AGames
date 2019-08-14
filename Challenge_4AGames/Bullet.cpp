#include "stdafx.h"
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(Vector2f pos, Vector2f dir, float speed, float spawnTime, float lifeTime)
{
	this->position = pos;
	this->direction = dir;
	this->speed = speed;
	this->spawnTime = spawnTime;
	this->lifeTime = lifeTime;

	this->renderShape.setFillColor(BULLET_COLOR);	//light green
	this->renderShape.setRadius(BULLET_RADIUS);

	this->SetActive(true);
}

Bullet::~Bullet()
{
}

void Bullet::Render(sf::RenderWindow * const windowPtr) const
{
	windowPtr->draw(this->renderShape);
}

void Bullet::SetNewDirection(Vector2f newDir)
{
	this->direction = newDir;
}

void Bullet::Move(float deltaTime)
{
	this->position += this->direction * this->speed * deltaTime;
	renderShape.setPosition(this->position);
}

float Bullet::GetDeathTime() const
{
	return spawnTime + lifeTime;
}

Vector2f Bullet::GetPosition() const
{
	return this->position;
}

Vector2f Bullet::GetDirection() const
{
	return this->direction;
}

float Bullet::GetSpawnTime() const
{
	return this->spawnTime;
}
