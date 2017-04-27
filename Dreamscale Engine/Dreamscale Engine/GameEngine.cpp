#include "GameEngine.h"

using namespace dse;

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
