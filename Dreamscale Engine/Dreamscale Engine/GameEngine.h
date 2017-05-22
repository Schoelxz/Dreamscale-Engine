#pragma once
#include "CollisionHandler.h"
#include "InputManager.h"
#include "ObjectHandler.h"
#include "ProjectHandler.h"
#include "TmxHandler.h"

#include <lua.hpp>
#include <LuaBridge.h>
#include <SFML\Graphics.hpp>
#include <iostream>



using namespace luabridge;

namespace dse
{
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		//ObjectHandler getObjHand();
		//InputManager inpManager();
		//CollisionHandler collision();
		//ProjectHandler project();
		void Update();
		//void testMove(float a, float b);
		//Temp Mouse and Rectangle Test
		sf::Mouse mouse;
		sf::RectangleShape rect;

		//sf::RectangleShape rect2;
		sf::Vector2f vect{ 50,50 };

	private:
		TmxHandler tmx;
		sf::RenderWindow window;
		//TODO: objHandler creates a tmxHandler class. Plz fix or something i guess babidibobidi.
		ObjectHandler objHandler;
		InputManager inpManager;
		CollisionHandler collision;
		ProjectHandler project;
	};
}