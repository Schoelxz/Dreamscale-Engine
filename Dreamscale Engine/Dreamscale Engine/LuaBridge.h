#pragma once
#include "TmxHandler.h"
#include "GameEngine.h"
#pragma comment(lib, "lua53.lib")
#include <lua.hpp>
#include <LuaBridge.h>
#include "SfmlObject.h"
#include "CircleShape.h"

namespace dse
{

	class LuaBridge
	{
	public:
		LuaBridge();
		~LuaBridge();

		void DoLuaBridge(); //Or more accurately do lua binding
		int StartLuaScript();
		lua_State* L = luaL_newstate();

	};
}
