#include "GameEngine.h"



GameEngine::GameEngine()
{
	std::cout << "class:	GameEngine:	Constructed!" << std::endl;
}


GameEngine::~GameEngine()
{
	std::cout << "class:	GameEngine:	Destructed!" << std::endl;
}



ObjectHandler* GameEngine::getObjHand()
{
	return &objHandler;
}
