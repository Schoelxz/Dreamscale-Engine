#ifndef DREAMSCALEENGINE_LUABRIDGE_H_
#define DREAMSCALEENGINE_LUABRIDGE_H_

#include "TmxHandler.h"
#pragma comment(lib, "lua53.lib")
#include <lua.hpp>
#include <LuaBridge.h>
#include "SfmlObject.h"
#include "CircleShape.h"

namespace dse
{
	//Joel's code
	class LuaBridge
	{
	public:
		lua_State* L = luaL_newstate();

		LuaBridge();
		~LuaBridge();

		//Binds C++ and Lua.
		void BindLua();

		//Starts the given Lua script.
		int StartLuaScript(const char* path);
	};
}
#endif