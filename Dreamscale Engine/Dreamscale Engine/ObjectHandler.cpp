#include "ObjectHandler.h"

using namespace dse;

ObjectHandler::ObjectHandler()
{
	std::cout << "class:	ObjectHandler:	Constructed!" << std::endl;
}

ObjectHandler::~ObjectHandler()
{
	std::cout << "class:	ObjectHandler:	Destroyed!" << std::endl;
}

std::vector<GameObject*> ObjectHandler::getObject()
{
	return gameObject;
}

void ObjectHandler::createNewObject()
{
	gameObject.push_back(new GameObject);
}

void ObjectHandler::destroyObject(GameObject* object)
{
	for (size_t i = 0; i < gameObject.size(); i++)
	{
		if (gameObject[i] == object)
		{
			delete gameObject[i]; // Delete the pointer
			gameObject.erase(gameObject.begin() + i);  // Erase from vector!
			return;
		}
	}
}

void dse::ObjectHandler::getObjects(std::vector<GameObject*> objects)
{
	std::cout << objects.size() << " objects left in the vector" << std::endl;
}



