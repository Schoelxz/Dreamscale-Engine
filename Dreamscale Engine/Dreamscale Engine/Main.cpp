//Dreamscale Engine
//x86
#pragma comment(lib, "lua53.lib")
#include <lua.hpp>
#include <LuaBridge.h>

#include "LuaBridge.h"
using namespace luabridge;

//TODO: asdf2 = GameEngine.FindObject("name"); (.lua script)

int main()
{
	LuaBridge LuaTester;
	//SfmlObject BlueRectangle("BlueRectangle");

	sf::RenderWindow window;
	window.create(sf::VideoMode(1024, 768), "DreamScale Engine");

	LuaTester.DoLuaBridge();

	//LuaRef used for intertwine code more between cpp and lua
	//luabridge::LuaRef setPosition = luabridge::getGlobal(L, "SetPosition");
	//luabridge::LuaRef setSize = luabridge::getGlobal(L, "SetSize");

	//SfmlObject::GetAllObjects()
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
		
		for (auto v : SfmlObject::GetAllObjects())
		{
			//if (v->GetInstanceName() != "BlueRectangle")
				window.draw(v->rectShape);
			//else
				//std::cout << "yo" << std::endl;
		}

		window.display();
	}




}