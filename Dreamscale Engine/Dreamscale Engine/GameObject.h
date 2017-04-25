#pragma once
#include <iostream>
#include "Components.h"
#include <SFML\Graphics.hpp>

namespace dse
{
	class GameObject
	{
	public:

		GameObject();
		~GameObject();
	private:

		Transform transform;

		sf::Sprite sprite;

	};

}