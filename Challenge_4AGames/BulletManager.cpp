#include "stdafx.h"
#include "BulletManager.h"
#include <cstdio>
#include <ctime>

#define LOG_ENABLED

BulletManager::BulletManager()
{
	this->globalTime = 0;
}

BulletManager::~BulletManager()
{
	walls.clear();
	SyncWriteToReadBuffer();	//if something is still in write queue, blit it to read buffer and destroy it
	readBuffer.clear();
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
		readBuffer.push_back(writeBuffer.front());
		writeBuffer.pop();
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
			readBuffer.erase(readBuffer.begin() + i);
			continue;
		}

		if (bullet.IsActive())	//bullet is active = spawn time is greater or equal then current global time
		{
			//walls iteration and intersection 
			float deltaCache = deltaTime;
			sf::Vector2f intersPtr(0, 0);

			while (deltaCache > 0)
			{
				bool intersect = false;

				for (size_t j = 0; j < walls.size(); j++)
				{
					Segment& wall = walls[j];
					//if (MathHelper::Magnitude(wall.GetPoint(0) - bullet.GetPosition()) > bullet.GetSpeed() * deltaTime &&
					//	MathHelper::Magnitude(wall.GetPoint(1) - bullet.GetPosition()) > bullet.GetSpeed() * deltaTime)
					//	continue;	//600k iterations 5fps average. not so much improvement

					//the bullet is treated like a point
					intersect = wall.Intersect(bullet.GetPosition(), bullet.SimulateMove(deltaCache), &intersPtr);
					if (intersect)
					{
						//calculate delta passed before the intersection
						float dt = abs((MathHelper::Magnitude(bullet.GetPosition() - intersPtr))) / bullet.GetSpeed();

						deltaCache -= dt;

						//move based on this delta
						bullet.Move(dt);

						//reflect the bullet direction
						sf::Vector2f reflectedDir = wall.Reflect(bullet.GetDirection());
						bullet.SetNewDirection(reflectedDir);

						walls.erase(walls.begin() + j);
						break;
					}
				}

				if (!intersect)
				{ 
					bullet.Move(deltaCache);
					deltaCache = -1;
				}
			}
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
	Bullet newBullet(pos, dir, speed, spawnTime, lifeTime);
	newBullet.SetActive(spawnTime <= globalTime && lifeTime > globalTime);
	/*std::cout << "is active -> " << ((spawnTime <= globalTime && lifeTime > globalTime) ? "true" : "false") << std::endl;
	std::cout << "spawntime -> " << spawnTime << std::endl;
	std::cout << "life time -> " << lifeTime << std::endl;
	std::cout << "global time -> " << globalTime << std::endl;*/

	this->AddBulletToSimulation(std::move(newBullet));
}
