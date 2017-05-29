#include "ObjectHandler.h"
#include <iostream>

using namespace dse;

ObjectHandler::ObjectHandler()
{
	std::cout << "class:	ObjectHandler:	Constructed!" << std::endl;
}

ObjectHandler::~ObjectHandler()
{
	std::cout << "class:	ObjectHandler:	Destroyed!" << std::endl;
}

void dse::ObjectHandler::Update()
{
	
}

void dse::ObjectHandler::DrawObjects(sf::RenderWindow& win)
{
	//tmx.DrawMap(win);
	//tmx.DrawObjects(win);
}