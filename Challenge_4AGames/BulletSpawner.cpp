#include "BulletSpawner.h"

BulletSpawner::BulletSpawner(int minRateMs, int maxRateMs, BulletManager* manager)
{
	this->minRate = minRateMs;
	this->maxRate = maxRateMs;
	this->manager = manager;

	myThread = std::thread(&BulletSpawner::Run, this);
}

BulletSpawner::~BulletSpawner()
{
	killFlag = true;
	this->myThread.join();	//to be sure the thread finish its job. avoid leak
}

void BulletSpawner::Run()
{
	int sleepTime = 0;
	int range = maxRate - minRate;
	if (range == 0)
		range = maxRate;

	while (!killFlag)
	{
		//sleepTime = rand() % (int)range + minRate;
		sleepTime = GetRandom(maxRate, minRate);
		int sleepMs = sleepTime;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));

		CallFireFromOtherThread();
	}

	std::cout << "thread killed" << std::endl;
}

void BulletSpawner::CallFireFromOtherThread() const
{
	float posX = GetRandom(WINDOW_W);
	float posY = GetRandom(WINDOW_H);

	float dirX = GetRandom(WINDOW_W) - posX;
	float dirY = GetRandom(WINDOW_H) - posY;
	Vector2f dir(dirX, dirY);
	dir = MathHelper::Normalized(dir);

	float lifeTime = GetRandom(10);

	manager->Fire(Vector2f(posX, posY), dir, BULLET_SPEED, manager->GetGlobalTime() + GetRandom(10), lifeTime);
}