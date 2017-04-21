#include "GameEngine.h"



GameEngine::GameEngine()
{
	std::cout << "class: GameEngine : Constructed!" << std::endl;
	objHandler.objCreator();
	objHandler.objCreator();
	objHandler.objCreator();
	objHandler.objCreator();
}


GameEngine::~GameEngine()
{
	std::cout << "class: GameEngine : Destructed!" << std::endl;
}
