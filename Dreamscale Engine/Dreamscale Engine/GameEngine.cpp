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

	window.create(sf::VideoMode().getDesktopMode(), "DreamScale Engine");

	tmx.allFileNames = tmx.get_all_files_names_within_folder("./");
	tmx.ParseAllMaps();
	
	
	sf::View view2;
	view2.setCenter(sf::Vector2f(350, 300));
	float aspectRatio = (float)window.getSize().x / (float)window.getSize().y;

	const float viewSize = 320.0f;
	view2.setSize(sf::Vector2f(viewSize, viewSize / aspectRatio));

	view2.zoom(3);

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
					tmx.ResetVector();
					tmx.LoadMap(tmx.mapVector[tmx.allFileNames[0]]);
					tmx.LoadObjects(*tmx.mapVector[tmx.allFileNames[0]]);
					
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					tmx.ResetVector();
					tmx.LoadMap(tmx.mapVector[tmx.allFileNames[1]]);
					tmx.LoadObjects(*tmx.mapVector[tmx.allFileNames[1]]);
				}
			}
			if (event.type == sf::Event::MouseEntered)
				mouseInsideAWindow = true;
			if (event.type == sf::Event::MouseLeft)
				mouseInsideAWindow = false;
		}
		
		view2.setCenter(0, window.getSize().y / 5);
		if (mouseInsideAWindow)
		view2.move(mouse.getPosition(window).x, mouse.getPosition(window).y);

		//Temp MR
		if(mouseInsideAWindow)
		rect.setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y);

		window.clear();


		objHandler.Update();
		objHandler.DrawObjects(window);
		tmx.DrawMap(window);
		tmx.UpdateObjects();
		tmx.DrawObjects(window);

		window.setView(view2);


		window.draw(rect);//Temp MR

		window.display();
	}
}

//void dse::GameEngine::testMove(float a, float b)
//{
//	rect2.move(a, b);
//}

GameEngine::~GameEngine()
{
	std::cout << "class:	GameEngine:	Destructed!" << std::endl;
}