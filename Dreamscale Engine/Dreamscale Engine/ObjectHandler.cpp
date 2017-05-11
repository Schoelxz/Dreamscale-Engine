#include "ObjectHandler.h"
#include <iostream>

using namespace dse;

ObjectHandler::ObjectHandler()
{
	std::cout << "class:	ObjectHandler:	Constructed!" << std::endl;

	tmx.LoadMap();
	tmx.LoadObjects();
	//for (int i = 0; i < tmx.spriteVector.size(); i++) {
	//	gameObject.push_back(new sf::Sprite(tmx.GetObjects(i)));
	//	std::cout << gameObject[i]->getPosition().x << " " << gameObject[i]->getPosition().y << std::endl;
	//}
	std::cout << gameObject.size() << std::endl;
	//SetObjectType();
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
	tmx.DrawMap(win);
	tmx.DrawObjects(win);
}