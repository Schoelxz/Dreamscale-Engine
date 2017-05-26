#pragma once
#include "TmxHandler.h"
#include "GameEngine.h"
#pragma comment(lib, "lua53.lib")
#include <lua.hpp>
#include <LuaBridge.h>
#include "SfmlObject.h"

class LuaBridge
{
public:
	LuaBridge();
	~LuaBridge();

	void DoLuaBridge(); //This is also known as doing the bind _/-(*_*)-\_
	int StartLuaScript();
	lua_State* L = luaL_newstate();

};

