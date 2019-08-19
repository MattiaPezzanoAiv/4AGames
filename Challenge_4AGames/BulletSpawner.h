#pragma once
#include "Defines.h"
#include "BulletManager.h"
#include <thread>
#include <stdlib.h>
#include <iostream>
#include <random>

class BulletSpawner
{
public:
	BulletSpawner(int minRateMs, int maxRateMs, BulletManager* manager);
	~BulletSpawner();

	int minRate, maxRate;

	//should implement the thread code
	void Run();

	// random number generator from Stroustrup: 
	// http://www.stroustrup.com/C++11FAQ.html#std-random
	int GetRandom(int max, int min = 0) const
	{
		static std::default_random_engine re{};
		using Dist = std::uniform_int_distribution<int>;
		static Dist uid{};
		return uid(re, Dist::param_type{ min, max });
	}

private:
	BulletManager * manager;
	void CallFireFromOtherThread() const;

	std::thread myThread;
	bool killFlag = false;
};

