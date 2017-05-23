//Dreamscale Engine
//x86
#pragma comment(lib, "lua53.lib")
#include <lua.hpp>
#include <LuaBridge.h>
#include "GameEngine.h"
#include "SfmlObject.h"
using namespace luabridge;

//TODO: asdf2 = GameEngine.FindObject("name"); (.lua script)

int main()
{
	SfmlObject BlueRectangle("BlueRectangle");

	sf::RenderWindow window;
	window.create(sf::VideoMode(1024, 768), "DreamScale Engine");

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	getGlobalNamespace(L)
		.beginNamespace("GameEngine")
			.addFunction("FindObject", &SfmlObject::Find)
			.beginClass<SfmlObject>("SfmlObject")
				.addConstructor<void(*)(void)>()
				.addFunction("SetPosition",	 &SfmlObject::SetPosition)
				.addFunction("SetSize",		 &SfmlObject::SetSize)
		.endClass()
		.beginClass<dse::GameEngine>("Engine")
		.addConstructor<void(*)(void)>()
		.addFunction("StartUpdate", &dse::GameEngine::Update)
		
			.endClass();

	//luabridge::LuaRef setPosition = luabridge::getGlobal(L, "SetPosition");
	//luabridge::LuaRef setSize = luabridge::getGlobal(L, "SetSize");

	//BlueRectangle.SetPosition(50, 50);
	//BlueRectangle.SetSize(50, 50);

	BlueRectangle.rectShape.setFillColor(sf::Color::Blue);
	BlueRectangle.rectShape.setSize(sf::Vector2f(32.0f, 32.0f));
	BlueRectangle.rectShape.setPosition(sf::Vector2f(0.0f, 0.0f));

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
					if (luaL_dofile(L, "test.lua"))
					{
						// If Lua encountered an error, we can find at ontop of the stack
						std::cerr << lua_tostring(L, -1) << std::endl;
						// Return 1 as an error code
						return 1;
					}
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