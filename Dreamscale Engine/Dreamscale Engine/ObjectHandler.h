#ifndef DREAMSCALEENGINE_OBJECTHANDLER_H_
#define DREAMSCALEENGINE_OBJECTHANDLER_H_

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
		
		void DrawObjects(sf::RenderWindow&);

	private:
		std::vector<sf::Sprite*> m_game_objects;
	};
}

#endif