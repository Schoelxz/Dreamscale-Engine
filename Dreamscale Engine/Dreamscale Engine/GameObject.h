#pragma once
#include <iostream>
#include "Components.h"
#include <SFML\Graphics.hpp>

namespace dse
{
	class GameObject
	{
	public:

		Object getObjectInfo();

		GameObject();
		~GameObject();
	private:
		//sf::Sprite sprite; //to be used when sprite is removed from components.
		Object object;
		

	};

}