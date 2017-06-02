#ifndef DREAMSCALEENGINE_GAMEENGINE_H_
#define DREAMSCALEENGINE_GAMEENGINE_H_

#include "ObjectHandler.h"
#include "TmxHandler.h"

#include <lua.hpp>
#include <LuaBridge.h>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace luabridge;

namespace dse
{
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();
		
		void Update();
		TmxHandler* GetTmxHandler() const;

	private:
		TmxHandler* m_tmx;
		sf::RenderWindow m_window;
		ObjectHandler m_obj_handler;
	};
}
#endif