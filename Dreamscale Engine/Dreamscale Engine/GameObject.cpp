#include "GameObject.h"

using namespace dse;

GameObject::GameObject()
{
	std::cout << "class:	GameObject:	Constructed!" << std::endl;

	/*
	sprite.setPosition(0, 0);
	
	transform.position.setPosition(5, 3);

	std::cout << transform.position.getPosition().x << std::endl;
	*/
	
}

GameObject::~GameObject()
{
	std::cout << "class:	GameObject:	Destroyed!" << std::endl;

}


