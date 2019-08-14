#pragma once
#include "Defines.h"
#include "SFML\Graphics.hpp"
#include "BulletManager.h"
#include <string>

#define FPS(x) "FPS -> " + std::to_string(x)
#define BULLET_COUNT(x) "Bullet Count -> " + std::to_string(x)
#define GLOBAL_TIME(x) "Time -> " + std::to_string(x)

class Engine
{
public:
	Engine(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle, int targetFrameRate = 60);
	Engine(const Engine& copy) = delete;
	~Engine();

	BulletManager* bulletManagerPtr;

	//run the simulation
	void Run();

	void AddDrawable(sf::Drawable* const drawable);

private:
	sf::RenderWindow* ctxPtr;
	sf::Clock clock;

	float globalTime, previousGlobalTime;

	//this method is one tick of the simulation
	void Tick();

	std::vector<sf::Drawable*> drawables;
};

