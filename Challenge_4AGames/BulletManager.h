#pragma once
#include "Segment.h"
#include "Bullet.h"
#include <vector>
#include <queue>
#include <mutex>
#include <iostream>

class BulletManager
{
public:
	Bullet * GetFirstBullet()
	{
		return readBuffer[0];
	}
	~BulletManager();

	void AddWall(Segment* wall);

	void Fire(Vector2f pos, Vector2f dir, float speed, float spawnTime, float lifeTime);

	void SyncWriteToReadBuffer();							//also this will lock

	void Update(float deltaTime);

	//rendering
	void RenderWalls(sf::RenderWindow* const windowPtr) const;
	//this will render only the updated read buffer
	void RenderBullets(sf::RenderWindow* const windowPtr) const;

	float GetGlobalTime() const;
	int GetBulletCount() const;
	int GetWallCount() const;

private:
	float globalTime;

	//lock
	std::mutex mutex;

	std::vector<Segment*> walls;

	//input queue. this is supposed to handle the new incoming bullet from all threads
	//every time is accessed should be locked
	std::queue<Bullet*> writeBuffer;
	//after each frame the write buffer is added to this vector. This is supposed to contains all the bullets active in the current frame 
	//used to simulate the step
	std::vector<Bullet*> readBuffer;

	//write buffer manipulation
	void AddBulletToSimulation(Bullet* newBullet);	//this will lock

};

