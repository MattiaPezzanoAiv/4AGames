#include "stdafx.h"
#include "BulletSpawner.h"

BulletSpawner::BulletSpawner(int minRateMs, int maxRateMs, BulletManager* manager)
{
	this->minRate = minRateMs;
	this->maxRate = maxRateMs;
	this->manager = manager;

	myThread = std::thread(&BulletSpawner::Run, this);	//ptr to function
}

BulletSpawner::~BulletSpawner()
{
	killFlag = true;
	this->myThread.join();	//to be sure the thread finish is job. avoid leak
}

void BulletSpawner::Run()
{
	float sleepTime = 0;
	float range = maxRate - minRate;
	if (range == 0)
		range = maxRate;

	while (!killFlag)
	{
		sleepTime = rand() % (int)range + minRate;
		int sleepMs = sleepTime;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));

		CallFireFromOtherThread();
	}

	std::cout << "thread killed" << std::endl;
}

void BulletSpawner::CallFireFromOtherThread() const
{
	float posX = rand() % WINDOW_W;
	float posY = rand() % WINDOW_H;

	float dirX = (rand() % WINDOW_W) - posX;
	float dirY = (rand() % WINDOW_H) - posY;
	Vector2f dir(dirX, dirY);
	dir = VectorHelper::Normalized(dir);

	float lifeTime = rand() % 10;

	manager->Fire(Vector2f(posX, posY), dir, BULLET_SPEED, manager->GetGlobalTime() + rand() % 10, lifeTime);
	std::cout << "spawned bullet from thread at pos -> X: " << posX << " Y: " << posY << std::endl;
}
