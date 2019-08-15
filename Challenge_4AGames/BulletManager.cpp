#include "stdafx.h"
#include "BulletManager.h"
#include <cstdio>
#include <ctime>

#define LOG_ENABLED

BulletManager::~BulletManager()
{
	//destroy all walls
	/*for (size_t i = 0; i < walls.size(); i++)
	{
		Segment& ptr = walls[i];
		if (ptr == nullptr)
			continue;

		delete ptr;
	}*/
	
	walls.clear();
	SyncWriteToReadBuffer();	//if something is still in write queue, blit it to read buffer and destroy it
	readBuffer.clear();

	//destroy all bullets
	/*for (size_t i = 0; i < readBuffer.size(); i++)
	{
		Bullet& ptr = readBuffer[i];
		if (ptr == nullptr)
			continue;

		delete ptr;
	}*/
}

void BulletManager::AddWall(Segment wall)
{
	walls.push_back(wall);
}

void BulletManager::AddBulletToSimulation(Bullet newBullet)
{
	//start lock resources
	std::lock_guard<std::mutex> lock(this->mutex);		//This should be released when it goes out of scope

	writeBuffer.push(newBullet);	//added a new bullet
}

void BulletManager::SyncWriteToReadBuffer()
{
	//start lock resources	
	//noone should be able to access the buffer during sync with read buffer
	std::lock_guard<std::mutex> lock(this->mutex);

	while (writeBuffer.size() > 0)
	{
		readBuffer.push_back(writeBuffer.front());	//add the element
		writeBuffer.pop();							//really remove that from queue
	}
}

void BulletManager::Update(float deltaTime)
{
	std::clock_t start;
	double duration;

	start = std::clock();

	globalTime += deltaTime;

	//Move bullet and check for its collision
	size_t i = 0;
	while (i < readBuffer.size())
	{
		Bullet& bullet = readBuffer[i];
		if (globalTime >= bullet.GetSpawnTime() && !bullet.IsActive())	//it's time to join
			bullet.SetActive(true);

		//it's time to destroy a bullet
		if (bullet.GetDeathTime() <= this->globalTime)
		{
			//kill ptr and remove from vector (in this case I don't need to increase i)
			/*Bullet* tmp = readBuffer[i];
			delete tmp;*/
			readBuffer.erase(readBuffer.begin() + i);
			continue;
		}

		if (bullet.IsActive())	//bullet is active = spawn time is greater or equal then current global time
		{
			//walls iteration and intersection 
			bool intersect = false;
			for (size_t j = 0; j < walls.size(); j++)
			{
				Segment& wall = walls[j];
				if(VectorHelper::Magnitude(wall.GetPoint(0) - bullet.GetPosition()) > 100 &&
					VectorHelper::Magnitude(wall.GetPoint(1) - bullet.GetPosition()) > 100)
					continue;	//600k iterations 5fps average. not so much improvement

				sf::Vector2f pos = wall.GetPoint(0);
				sf::Vector2f dir = VectorHelper::Normalized(wall.GetPoint(0) - pos);
				sf::Vector2f intersection;
				//intersect = walls[i]->RayIntersectsSphere(pos, dir, *bullet, &intersection);
				intersect = wall.Intersect(bullet);
				if (intersect)
				{
					//reflect the bullet direction
					sf::Vector2f reflectedDir = wall.Reflect(bullet.GetDirection());
					bullet.SetNewDirection(reflectedDir);

					//delete walls[j];
					walls.erase(walls.begin() + j);
					break;
				}
			}

			bullet.Move(deltaTime);
		}
		i++;
	}
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
}

void BulletManager::RenderWalls(sf::RenderWindow* const windowPtr) const
{
	for (const Segment& wall : walls)
	{
		wall.Render(windowPtr);
	}
}

void BulletManager::RenderBullets(sf::RenderWindow * const windowPtr) const
{
	for (const Bullet& bullet : readBuffer)
	{
		if (bullet.IsActive())
			bullet.Render(windowPtr);
	}
}

float BulletManager::GetGlobalTime() const
{
	return this->globalTime;
}

int BulletManager::GetBulletCount() const
{
	return readBuffer.size();
}

int BulletManager::GetWallCount() const
{
	return walls.size();
}

void BulletManager::Fire(Vector2f pos, Vector2f dir, float speed, float spawnTime, float lifeTime)
{
	//is the address constant?
	Bullet newBullet(pos, dir, speed, spawnTime, lifeTime);
	newBullet.SetActive(spawnTime <= globalTime && lifeTime > globalTime);

	this->AddBulletToSimulation(std::move(newBullet));
}
