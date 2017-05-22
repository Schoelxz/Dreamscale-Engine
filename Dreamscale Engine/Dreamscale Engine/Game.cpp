#include "Game.h"

void Game::Start()
{
	window.create(sf::VideoMode(1800, 640), "Snake");

	Run();
}

void Game::Run()
{
	sf::Event event;
	sf::Clock clock;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}


			//Get the time since last frame
			float deltaTime = clock.restart().asSeconds();

			
			window.clear();

			window.display();


		}
		
	}
}