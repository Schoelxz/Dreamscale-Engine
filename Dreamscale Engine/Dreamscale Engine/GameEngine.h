#ifndef DREAMSCALEENGINE_GAMEENGINE_H_
#define DREAMSCALEENGINE_GAMEENGINE_H_

#include <lua.hpp>
#include <LuaBridge.h>
#pragma comment(lib, "lua53.lib")
#include <SFML\Graphics.hpp>
#include <iostream>

#include "TmxHandler.h"
#include "SfmlObject.h"

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
		SfmlObject m_test_object;
		int m_position_temp = 0;
	};
}
#endif