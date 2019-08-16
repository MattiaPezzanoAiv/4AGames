#include "../Challenge_4AGames/Defines.h"
#include "Segment.h"
#include <iostream>
#include "../Challenge_4AGames/BulletManager.h"
#include "../Challenge_4AGames/Grid.h"
#include "../Challenge_4AGames/BulletSpawner.h"
#include <string>
#include <crtdbg.h>

#define FORMAT_TEXT(str, n) str + std::to_string(n)

//check for fucking stupid comments

int main()
{
	BulletManager manager;

	Grid grid(15, 15);
	grid.DistributeSegments(&manager);
	
	/*Segment w1(sf::Vector2f(0, -50), sf::Vector2f(0, 50));
	Segment w2(sf::Vector2f(200, -50), sf::Vector2f(200, 50));
	manager.AddWall(std::move(w1));
	manager.AddWall(std::move(w2));
	*/

	manager.SyncWriteToReadBuffer();

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Test window");

	sf::Clock clock;

	//load font
	sf::Font arial;
	if (!arial.loadFromFile("Assets/font.ttf"))
	{
		std::cout << "Font file not found" << std::endl;
		system("pause");
		return -1;
	}

	//text for fps
	sf::Text fpsText;
	fpsText.setFont(arial);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::Red);
	fpsText.setString(FORMAT_TEXT("FPS -> ", 0));

	//text for bullet count
	sf::Text bulletCountText;
	bulletCountText.setFont(arial);
	bulletCountText.setCharacterSize(24);
	bulletCountText.setFillColor(sf::Color::Red);
	bulletCountText.setString(FORMAT_TEXT("Bullet count -> ", 0));
	bulletCountText.setPosition(0, 30);

	//text for global time
	sf::Text wallCountText;
	wallCountText.setFont(arial);
	wallCountText.setCharacterSize(24);
	wallCountText.setFillColor(sf::Color::Red);
	wallCountText.setPosition(0, 60);
	wallCountText.setString(FORMAT_TEXT("Wall count -> ", 0));

	//text for global time
	sf::Text gloablTimeText;
	gloablTimeText.setFont(arial);
	gloablTimeText.setCharacterSize(24);
	gloablTimeText.setFillColor(sf::Color::Red);
	gloablTimeText.setPosition(0, 90);
	gloablTimeText.setString(FORMAT_TEXT("Time -> ", 0));

	{	//using a scope to be sure that threads are cleaned up before the bullet manager. in this way I'm sure there aren't bullet spawned during 
		//manager clean up (thread use join <---)

		//start threads
		BulletSpawner spawner2(100, 200, &manager);
		BulletSpawner spawner3(100, 200, &manager);
		BulletSpawner spawner4(100, 200, &manager);
		BulletSpawner spawner5(100, 200, &manager);

		//manager.Fire(sf::Vector2f(100, 0), sf::Vector2f(1, 0), 100, 0, 5000);

		window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(true);

		while (window.isOpen())
		{
			sf::Time deltaTime = clock.restart();

			sf::Event event;
			while (window.pollEvent(event))
			{
				// Close window: exit
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//logic frame
			manager.SyncWriteToReadBuffer();
			manager.Update(deltaTime.asSeconds());

			//rendering frame
			window.clear();

			manager.RenderWalls(&window);
			manager.RenderBullets(&window);

			window.draw(fpsText);
			window.draw(bulletCountText);
			window.draw(wallCountText);
			window.draw(gloablTimeText);

			window.display();

			//update texts content
			fpsText.setString(FORMAT_TEXT("FPS -> ", 1.0f / deltaTime.asSeconds()));
			bulletCountText.setString(FORMAT_TEXT("Bullet count -> ", manager.GetBulletCount()));
			wallCountText.setString(FORMAT_TEXT("Wall count -> ", manager.GetWallCount()));
			gloablTimeText.setString(FORMAT_TEXT("Time -> ", manager.GetGlobalTime()));
		}
	}

	/*_CrtDumpMemoryLeaks();
	system("pause");*/
	return 0;
}

