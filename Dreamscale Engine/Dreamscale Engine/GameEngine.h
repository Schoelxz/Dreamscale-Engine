#pragma once
#include <iostream>
#include "CollisionHandler.h"
#include "InputManager.h"
#include "ObjectHandler.h"
#include "ProjectHandler.h"
#include <SFML\Graphics.hpp>

using namespace dse;

class GameEngine
{
public:
	ObjectHandler getObjHand();
	//InputManager inpManager();
	//CollisionHandler collision();
	//ProjectHandler project();


	GameEngine();
	~GameEngine();
	
private:

	ObjectHandler objHandler;
	InputManager inpManager;
	CollisionHandler collision;
	ProjectHandler project;


};

