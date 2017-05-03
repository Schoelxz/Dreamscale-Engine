#include "GameEngine.h"




using namespace dse;

GameEngine::GameEngine()
{
	window.create(sf::VideoMode(1920, 1080), "DreamScale Engine");
	tmx.LoadMap();
	tmx.LoadObjects();
	std::cout << "class:	GameEngine:	Constructed!" << std::endl;
}

void dse::GameEngine::Update()
{
	//Temp MR
	rect.setFillColor(sf::Color::Green);
	rect.setSize(vect);

	while (window.isOpen())
	{
		sf::Event event;
		// Poll events for this window
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
		}

		//Temp MR
		rect.setPosition(mouse.getPosition().x, mouse.getPosition().y);

		window.clear();

		tmx.DrawMap(window);
		tmx.DrawObjects(window);
		window.draw(rect);//Temp MR

		window.display();
	}
}

GameEngine::~GameEngine()
{
	std::cout << "class:	GameEngine:	Destructed!" << std::endl;
}



ObjectHandler* GameEngine::getObjHand()
{
	return &objHandler;
}
