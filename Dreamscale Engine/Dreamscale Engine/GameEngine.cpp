#include "GameEngine.h"




using namespace dse;

GameEngine::GameEngine()
{
	std::cout << "class:	GameEngine:	Constructed!" << std::endl;
	window.create(sf::VideoMode(1024, 768), "DreamScale Engine");
	tmx.LoadMap();
	tmx.LoadObjects();
}

void dse::GameEngine::Update()
{
	//Temp MR
	rect.setFillColor(sf::Color::Green);
	rect.setSize(vect);

	bool mouseInsideAWindow = false;

	sf::View view2;
	view2.setCenter(sf::Vector2f(350, 300));
	view2.setSize(sf::Vector2f(200, 200));

	view2.zoom(8);

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
			if (event.type == sf::Event::MouseEntered)
				mouseInsideAWindow = true;
			if (event.type == sf::Event::MouseLeft)
				mouseInsideAWindow = false;
		}
		
		view2.setCenter(400, 400);
		if (mouseInsideAWindow)
		view2.move(mouse.getPosition(window).x, mouse.getPosition(window).y);

		//Temp MR
		if(mouseInsideAWindow)
		rect.setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y);

		window.clear();
		window.setView(view2);
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
