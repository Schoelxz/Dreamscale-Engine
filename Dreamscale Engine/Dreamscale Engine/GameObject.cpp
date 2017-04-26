#include "GameObject.h"

using namespace dse;

GameObject::GameObject()
{
	std::cout << "class:	GameObject:	Constructed!" << std::endl;
}

GameObject::~GameObject()
{
	std::cout << "class:	GameObject:	Destroyed!" << std::endl;
}

Object GameObject::getObjectInfo()
{
	return object;
}


