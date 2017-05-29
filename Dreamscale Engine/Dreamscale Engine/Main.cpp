//Dreamscale Engine
//x86
#pragma comment(lib, "lua53.lib")
#include <lua.hpp>
#include "LuaBridge.h"

using namespace luabridge;
using namespace dse;

//TODO: asdf2 = GameEngine.FindObject("name"); (.lua script)
int main()
{
	LuaBridge LuaTester;
	dse::CircleShape circleShape;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1024, 768), "DreamScale Engine");

	LuaTester.DoLuaBridge();

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "najs" << std::endl;
					LuaTester.StartLuaScript();
				}
			}
		}
		window.clear();

	for (size_t i = 0; i < circleShape.GetCircleshapeVector().size(); i++)
			window.draw(*circleShape.GetCircleshapeVector()[i]);

		window.display();
	}
}