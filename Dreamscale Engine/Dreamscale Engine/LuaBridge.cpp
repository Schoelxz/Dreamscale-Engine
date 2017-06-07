#include "LuaBridge.h"
#include "GameEngine.h"

using namespace dse;

LuaBridge::LuaBridge()
{
}

LuaBridge::~LuaBridge()
{
}
//LuaRef used for intertwine code more between cpp and lua
//luabridge::LuaRef setPosition = luabridge::getGlobal(L, "SetPosition");
//luabridge::LuaRef setSize = luabridge::getGlobal(L, "SetSize");
void LuaBridge::BindLua()
{
	luaL_openlibs(L);
	getGlobalNamespace(L)
		.beginNamespace("GameEngine")

			.addFunction("FindObject", &SfmlObject::Find)

			.beginClass<SfmlObject>("SfmlObject")
				.addConstructor<void(*)(const std::string&)>()
				.addFunction("SetPosition", &SfmlObject::SetPosition)
				.addFunction("SetSize", &SfmlObject::SetSize)
			.endClass()

			.beginClass<dse::GameEngine>("Engine")
				.addConstructor<void(*)(void)>()
				.addFunction("GetTmxHandler", &dse::GameEngine::GetTmxHandler)
				.addFunction("StartUpdate", &dse::GameEngine::Update)
			.endClass()

			.beginClass<TmxHandler>("TmxHandler")
				.addFunction("ParseAllMaps", &TmxHandler::ParseAllMaps)
				.addFunction("GetDrawables", &TmxHandler::GetDrawable)
			.endClass()

			.beginClass<sf::Vector2f>("Vector2f")
				.addConstructor<void(*)(float, float)>()
				.addData("x", &sf::Vector2f::x)
				.addData("y", &sf::Vector2f::y)
			.endClass()

			.beginClass<dse::CircleShape>("CircleShape")
				.addConstructor<void(*)(void)>()
				.addProperty("visibility", &dse::CircleShape::GetVisible, &dse::CircleShape::SetVisible)
				.addProperty("type", &dse::CircleShape::GetType, &dse::CircleShape::SetType)
				.addProperty("name", &dse::CircleShape::GetName, &dse::CircleShape::SetName)
				.addProperty("position", &dse::CircleShape::GetPosition, &dse::CircleShape::SetPosition)
				.addProperty("radius", &dse::CircleShape::GetRadius, &dse::CircleShape::SetRadius)
			.endClass()

		.endNamespace();
}

int LuaBridge::StartLuaScript(const char* path)
{
	if (luaL_dofile(L, path))
	{
		// If Lua encountered an error, we can find at ontop of the stack
		std::cerr << lua_tostring(L, -1) << std::endl;
		// Return 1 as an error code
		return 1;
	}
}