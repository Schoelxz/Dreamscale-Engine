#include "LuaBridge.h"



LuaBridge::LuaBridge()
{
}


LuaBridge::~LuaBridge()
{
}

void LuaBridge::DoLuaBridge()
{
	
	luaL_openlibs(L);
	getGlobalNamespace(L)
		.beginNamespace("GameEngine")
		.addFunction("FindObject", &SfmlObject::Find)
		.beginClass<SfmlObject>("SfmlObject")
		.addConstructor<void(*)(void)>()
		.addFunction("SetPosition", &SfmlObject::SetPosition)
		.addFunction("SetSize", &SfmlObject::SetSize)
		.endClass()
		.beginClass<dse::GameEngine>("Engine")
		.addConstructor<void(*)(void)>()
		.addFunction("StartUpdate", &dse::GameEngine::Update)

		.endClass();
}

int LuaBridge::StartLuaScript()
{
	if (luaL_dofile(L, "test.lua"))
	{
		// If Lua encountered an error, we can find at ontop of the stack
		std::cerr << lua_tostring(L, -1) << std::endl;
		// Return 1 as an error code
		return 1;
	}
}
