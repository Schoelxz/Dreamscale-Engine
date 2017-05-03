#include "GameEngine.h"

using namespace dse;

GameEngine::GameEngine()
{
	window.create(sf::VideoMode(800, 600), "snek");
	tmx.LoadMap();
	tmx.LoadObjects();
	//std::cout << "class:	GameEngine:	Constructed!" << std::endl;
}

void dse::GameEngine::Update()
{

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

		window.clear();

		tmx.Draw(window);

		// Create a non-default renderstate, and bind our tileset texture to it
		//sf::RenderStates states;
		//states.texture = &tileSet;
		//for (auto i : vertexLayers)
		//{
		//	// Render a vertexarray, with the custom renderstate
		//	window.draw(*i, states);
		//}
		//for (int i = 0; i < spriteVector.size() - 1; i++)
		//{
		//	window.draw(*spriteVector[i]);
		//}
		window.display();
	}
}

GameEngine::~GameEngine()
{
	//std::cout << "class:	GameEngine:	Destructed!" << std::endl;
}



ObjectHandler* GameEngine::getObjHand()
{
	return &objHandler;
}
