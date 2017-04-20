#pragma once
#include <iostream>
#include "CollisionHandler.h"
#include "InputManager.h"
#include "ObjectHandler.h"
#include <SFML\Graphics.hpp>

class GameEngine
{
public:

	

	ObjectHandler objHandler;
	InputManager inpManager;
	CollisionHandler collision;

	GameEngine();
	~GameEngine();
};

