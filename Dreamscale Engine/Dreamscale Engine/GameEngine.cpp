#include "GameEngine.h"




using namespace dse;

GameEngine::GameEngine()
{
	std::cout << "class:	GameEngine:	Constructed!" << std::endl;
}

void dse::GameEngine::Update()
{
	//Temp MR
	rect.setFillColor(sf::Color::Green);
	rect.setSize(vect);

	bool mouseInsideAWindow = false;

	window.create(sf::VideoMode(1024, 768), "DreamScale Engine");

	tmx.ParseAllMaps();	

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
				if (event.key.code == sf::Keyboard::Left)
				{
					tmx.LoadMap(tmx.mapVector[tmx.GetTmxNames()[0]]);
					tmx.LoadObjects(*tmx.mapVector[tmx.GetTmxNames()[0]]);
					
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					tmx.LoadMap(tmx.mapVector[tmx.GetTmxNames()[1]]);
					tmx.LoadObjects(*tmx.mapVector[tmx.GetTmxNames()[1]]);
				}
			}
			if (event.type == sf::Event::MouseEntered)
				mouseInsideAWindow = true;
			if (event.type == sf::Event::MouseLeft)
				mouseInsideAWindow = false;
		}

		//Temp MR
		if(mouseInsideAWindow)
		rect.setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y);

		window.clear();

		objHandler.Update();
		objHandler.DrawObjects(window);
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