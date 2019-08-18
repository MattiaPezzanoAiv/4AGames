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
	dir = MathHelper::Normalized(dir);

	float lifeTime = rand() % 10;

	manager->Fire(Vector2f(posX, posY), dir, BULLET_SPEED, manager->GetGlobalTime() + rand() % 10, lifeTime);
}
