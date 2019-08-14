#pragma once
#include "Defines.h"
#include "BulletManager.h"
#include <thread>
#include <stdlib.h>
#include <iostream>

class BulletSpawner
{
public:
	BulletSpawner(int minRateMs, int maxRateMs, BulletManager* manager);
	~BulletSpawner();

	float minRate, maxRate;

	void Run();

private:
	BulletManager * manager;
	void CallFireFromOtherThread() const;

	std::thread myThread;
	bool killFlag = false;
};

