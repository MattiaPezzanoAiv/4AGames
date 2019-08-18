#include "BulletManager.h"
#include <cstdio>
#include <ctime>

#define PROFILING
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

	writeBuffer.push(newBullet);
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
#ifdef PROFILING
	std::clock_t start;
	double duration;
	start = std::clock();
#endif

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

		if (bullet.IsActive())
		{
			float deltaCache = deltaTime;

			sf::Vector2f cachedVector;
			//I use this cached vector to cache the final position in order to calculate it only one time
			//if there is a collision it's used to cache the intersection point

			sf::Vector2f cachedBulletPos = bullet.GetPosition();
			//I use this cached pos to avoid a method call to set position every collision and set 
			//the render object position every step (not useful because it will not be rendered)
			while (deltaCache > 0)
			{
				bool intersect = false;
				cachedVector = cachedBulletPos + bullet.GetDirection() * bullet.GetSpeed() * deltaCache;

				for (size_t j = 0; j < walls.size(); j++)
				{
					Segment& wall = walls[j];

					//the bullet is treated like a point
					intersect = wall.Intersect(cachedBulletPos, cachedVector, &cachedVector);
					if (intersect)
					{
						//calculate delta passed before the intersection
						float dt = abs((MathHelper::Magnitude(cachedBulletPos - cachedVector))) / bullet.GetSpeed();

						deltaCache -= dt;

						//move based on this delta
						cachedBulletPos = cachedVector;

						//reflect the bullet direction
						sf::Vector2f reflectedDir = wall.Reflect(bullet.GetDirection());
						bullet.SetNewDirection(reflectedDir);

						walls.erase(walls.begin() + j);
						break;
					}
				}
				if (!intersect)
				{
					cachedBulletPos = cachedVector;
					deltaCache = -1;
				}
			}
			bullet.SetPosition(cachedBulletPos);
		}
		i++;
	}

#ifdef PROFILING
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "update duration -> " << duration << std::endl;
#endif
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

	this->AddBulletToSimulation(std::move(newBullet));
}
