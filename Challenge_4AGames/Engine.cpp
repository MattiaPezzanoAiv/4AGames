#include "stdafx.h"
#include "Engine.h"


Engine * Engine::Instance()
{
	return nullptr;
}

Engine::Engine(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle, int targetFrameRate = 60)
{
	//ctx creation
	this->ctxPtr = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowTitle);
	this->ctxPtr->setFramerateLimit(targetFrameRate);

	//bullet manager creation
	this->bulletManagerPtr = new BulletManager();
}

Engine::~Engine()
{
	//releasing resources if !null
	if (this->ctxPtr != nullptr)
		delete this->ctxPtr;
	if (this->bulletManagerPtr != nullptr)
		delete this->bulletManagerPtr;
}

void Engine::Run()
{
	while (this->ctxPtr->isOpen())
	{
		//calculating delta and sum to global time
		sf::Time deltaTime = clock.restart();
		this->globalTime += deltaTime.asSeconds();
		this->bulletManagerPtr->SetGameTime(this->globalTime);	//update bullet manager global time

		//polling events 
		sf::Event event;
		while (this->ctxPtr->pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				this->ctxPtr->close();
		}

		this->bulletManagerPtr->SyncWriteToReadBuffer();
		this->bulletManagerPtr->Update(deltaTime.asSeconds());	
		
		Tick();
	}
}

void Engine::AddDrawable(sf::Drawable* const drawable)
{
	this->drawables.push_back(drawable);
}

void Engine::Tick()
{
	this->ctxPtr->clear();

	for (auto drawable : this->drawables)
	{
		this->ctxPtr->draw(*drawable);
	}

	this->ctxPtr->display();
}
