//Dreamscale Engine
//x86
#include "GameEngine.h"



int main()
{
	std::cout << "Dreamscale Engine" << std::endl;

	GameEngine gameEngine;
	gameEngine.~GameEngine();

	gameEngine.project.SetFilename("myFirstProject1.txt");
	gameEngine.project.SaveProject("This is my data in my project!!!");

	if (gameEngine.project.FileExists("myFirstProject1.txt"))
		std::cout << "File Exists!" << std::endl;

	//Min Super FIna kommentar, jag gillar den så braaaaaaaaaa.

	while (1); //dont use this. but use it anyway

	return 0;
}