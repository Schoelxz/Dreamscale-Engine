#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

#include "TmxHandler.h"

namespace dse
{

	static class ObjectHandler
	{
	public:
		ObjectHandler();
		~ObjectHandler();
		
		void Update();
		
		void DrawObjects(sf::RenderWindow& win);

	private:
		std::vector<sf::Sprite*> gameObject;
		//TmxHandler tmx;
	};
}
