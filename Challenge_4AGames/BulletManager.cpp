#include "stdafx.h"
#include "BulletManager.h"

#define LOG_ENABLED

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	//destroy all walls
	for (size_t i = 0; i < walls.size(); i++)
	{
		auto ptr = walls[i];
		if (ptr == nullptr)
			continue;

		delete ptr;
		walls[i] = nullptr;	//not usefull
	}

	SyncWriteToReadBuffer();	//if something is still in write queue, blit it to read buffer and destroy it

	//destroy all bullets
	for (size_t i = 0; i < readBuffer.size(); i++)
	{
		auto ptr = readBuffer[i];
		if (ptr == nullptr)
			continue;

		delete ptr;
		readBuffer[i] = nullptr;
	}

}

void BulletManager::AddWall(Segment* wall)
{
	walls.push_back(wall);
	std::cout << "Added new wall at -> " << wall << std::endl;
}

void BulletManager::AddBulletToSimulation(Bullet* const newBullet)
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
	globalTime += deltaTime;

	//Move bullet and check for its collision
	int i = 0;
	while(i < readBuffer.size())
	{
		if (globalTime >= readBuffer[i]->GetSpawnTime() && !readBuffer[i]->IsActive())	//it's time to join
			readBuffer[i]->SetActive(true);

		//it's time to destroy a bullet
		if (readBuffer[i]->GetDeathTime() <= this->globalTime)
		{
			//kill ptr and remove from vector (in this case I don't need to increase i)
			auto tmp = readBuffer[i];
			delete tmp;
			readBuffer.erase(readBuffer.begin() + i);
			continue;
		}

		if (readBuffer[i]->IsActive())	//bullet is active = spawn time is greater or equal then current global time
		{
			//walls iteration and intersection 
			bool intersect = false;
			for (size_t j = 0; j < walls.size(); j++)
			{
				if (!walls[j]->IsActive())
					continue;

				auto pos = walls[j]->GetPoint(0);
				auto dir = VectorHelper::Normalized(walls[j]->GetPoint(0) - pos);
				sf::Vector2f intersection;
				//intersect = walls[i]->RayIntersectsSphere(pos, dir, *bullet, &intersection);
				intersect = walls[j]->Intersect(*readBuffer[i]);
				if (intersect)
				{
					//reflect the bullet direction
					auto reflectedDir = walls[j]->Reflect(readBuffer[i]->GetDirection());
					readBuffer[i]->SetNewDirection(reflectedDir);

					//destroy the wall
					delete walls[j];
					walls.erase(walls.begin() + j);
					break;
				}
			}

			readBuffer[i]->Move(deltaTime);
		}
		i++;
	}
}

void BulletManager::RenderWalls(sf::RenderWindow* const windowPtr) const
{
	for (auto wall : walls)
	{
		if (wall->IsActive())
			wall->Render(windowPtr);
	}
}

void BulletManager::RenderBullets(sf::RenderWindow * const windowPtr) const
{
	for (auto bullet : readBuffer)
	{
		if (bullet->IsActive())
			bullet->Render(windowPtr);
	}
}

float BulletManager::GetGlobalTime() const
{
	return this->globalTime;
}

int BulletManager::GetBulletCount() const
{
	return readBuffer.size();
	/*int count = 0;
	for (auto e : readBuffer)
		count += e->IsActive() ? 1 : 0;
	return count;*/
}

int BulletManager::GetWallCount() const
{
	return walls.size();
}

void BulletManager::Fire(Vector2f pos, Vector2f dir, float speed, float spawnTime, float lifeTime)
{
	//is the address constant?
	Bullet* newBullet = new Bullet(pos, dir, speed, spawnTime, lifeTime);
	newBullet->SetActive(spawnTime <= globalTime && lifeTime > globalTime);

	this->AddBulletToSimulation(newBullet);
}
