#pragma once
#include "GameObject.h"
#include <vector>

class ObjectHandler
{
public:
	
	std::vector<GameObject*> gameObject;

	ObjectHandler();
	~ObjectHandler();
};

