#include "../Challenge_4AGames/Defines.h"
#include "Segment.h"
#include <iostream>
#include "../Challenge_4AGames/BulletManager.h"
#include "../Challenge_4AGames/BulletSpawner.h"
#include <string>
#include <crtdbg.h>

#define FORMAT_TEXT(str, n) str + std::to_string(n)

void SetupWallsGrid(BulletManager& manager)
{
	float cellW = WINDOW_W / 15.0f;
	float cellH = WINDOW_H / 15.0f;

	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			if (j > 0)
			{
				sf::Vector2f p1((j - 1) * cellW, i * cellH);
				sf::Vector2f p2(j * cellW, i * cellH);
				manager.AddWall(std::move(Segment(p1, p2)));
			}
			if (i > 0)
			{
				sf::Vector2f p1(j * cellW, (i - 1) * cellH);
				sf::Vector2f p2(j * cellW, i * cellH);
				manager.AddWall(std::move(Segment(p1, p2)));
			}
		}
	}
}

int main()
{
	BulletManager manager;

	SetupWallsGrid(manager);

	sf::Clock clock;

	//load font
	sf::Font arial;
	if (!arial.loadFromFile("Assets/font.ttf"))
	{
		std::cout << "Font file not found" << std::endl;
		system("pause");
		return -1;
	}

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Test window");

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

