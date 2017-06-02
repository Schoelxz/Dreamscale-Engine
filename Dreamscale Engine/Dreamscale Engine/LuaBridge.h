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
	class LuaBridge
	{
	public:
		LuaBridge();
		~LuaBridge();

		void BindLua(); //Or more accurately do lua binding
		int StartLuaScript(const char*);
		lua_State* L = luaL_newstate();
	};
}
#endif