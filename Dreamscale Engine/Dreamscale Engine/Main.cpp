//Dreamscale Engine
//x86
#include "GameEngine.h"
#include "ProjectHandler.h"

int main()
{
	std::cout << "Dreamscale Engine" << std::endl;

	GameEngine gameEngine;
	ProjectHandler project;

	std::string asdf1 = "jag är en super hydlarisk mekanism!";
	float asdf2 = 1;



	project.save(asdf1, asdf2);
	


	while (1); //dont use this. but use it anyway

	return 0;
}