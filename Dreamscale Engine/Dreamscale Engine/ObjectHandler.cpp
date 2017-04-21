#include "ObjectHandler.h"



ObjectHandler::ObjectHandler()
{
	std::cout << "class: ObjectHandler : Constructed!" << std::endl;
}

ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::objCreator()
{
	gameObject.push_back(new GameObject);
}
