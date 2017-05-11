#pragma once
#include <iostream>
#include "CollisionHandler.h"
#include "InputManager.h"
#include "ObjectHandler.h"
#include "ProjectHandler.h"
#include <lua.hpp>
#include <LuaBridge.h>
#include <SFML\Graphics.hpp>
#include "TmxHandler.h"


using namespace luabridge;

namespace dse
{

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		ObjectHandler* getObjHand();
		//InputManager inpManager();
		//CollisionHandler collision();
		//ProjectHandler project();
		
		void Update();

		//Temp Mouse and Rectangle Test
		sf::Mouse mouse;
		sf::RectangleShape rect;
		sf::Vector2f vect{ 50,50 };



	private:
		TmxHandler tmx;
		sf::RenderWindow window;
		ObjectHandler objHandler;
		InputManager inpManager;
		CollisionHandler collision;
		ProjectHandler project;
		
	};

}

