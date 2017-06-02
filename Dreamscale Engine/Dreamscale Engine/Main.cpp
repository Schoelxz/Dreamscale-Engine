//Dreamscale Engine
//x86
#pragma comment(lib, "lua53.lib")
#include <lua.hpp>
#include "GameEngine.h"


using namespace luabridge;
using namespace dse;

int main()
{
	GameEngine game_engine;
	//dse::CircleShape circleShape;

	game_engine.Update();

	return 0;
}