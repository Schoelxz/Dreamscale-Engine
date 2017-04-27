//Dreamscale Engine
//x86
#include "GameEngine.h"

#pragma comment(lib, "lua53.lib")

/*
using namespace dse;

int main()
{
	std::cout << "Dreamscale Engine" << std::endl;

	GameEngine gameEngine;

	while (1); //dont use this. but use it anyway

	return 0;
}*/



/*
int main()
{
GameEngine gameEngine;

return 0;
}*/

/*
// Creates a templated Bind function
template<typename T>
void Bind(lua_State* L)
{
T::DoBind(L);
}

using namespace luabridge;

class A
{
// Befriends the templated Bind-function so it can access our protected functions
friend void Bind<A>(lua_State*);

public:
A()
{
std::cout << "A created!" << std::endl;
}

virtual void Print(lua_State* L)
{
// Executes a string as Lua-code
luaL_dostring(L, "print ('called A::print')");
}

protected:
// Static function where we expose our call to Lua
static void DoBind(lua_State* L)
{
getGlobalNamespace(L)
.beginNamespace("GameEngine")
.beginClass<A>("A")
.addConstructor<void(*)(void)>()
.addFunction("Print", &A::Print)
.endClass()
.endNamespace();
}
};

class B : public A
{
// Befriends the templated Bind function so it can access our protected functions
friend void Bind<B>(lua_State*);

public:
B()
{
std::cout << "B created!" << std::endl;
}

virtual void Print(lua_State* L)
{
// Executes a string as Lua code
luaL_dostring(L, "print ('called B::print')");
}

protected:
// Expose our class and memberfunctions to Lua
static void DoBind(lua_State* L)
{
getGlobalNamespace(L)
.beginNamespace("GameEngine")
.deriveClass<B, A>("B")
.addConstructor<void(*)(void)>()
.addFunction("Print", &B::Print)
.endClass()
.endNamespace();
}
};


int main()
{
// Create a new lua_State and open default Lua-libraries
lua_State* L = luaL_newstate();
luaL_openlibs(L);

// Calls the templated Bind function, with our classes which should be exposed.
Bind<A>(L);
Bind<B>(L);

// If luaL_dofile returns anything other than 0, it's an error
if (luaL_dofile(L, "test.lua"))
{
// If Lua encountered an error, we can find at ontop of the stack
std::cerr << lua_tostring(L, -1) << std::endl;
// Return 1 as an error code
return 1;
}

// Get the global symbol add, and save it as a LuaRef
luabridge::LuaRef add = luabridge::getGlobal(L, "add");
// Call the global symbol add as a function, with 2 arguments
int sum = add(2, 9);
int apa;
// Print the result from our Lua add-function
std::cout << "The sum of 2 and 9 is: " << sum << std::endl;
std::cin >> apa;
// Return with success
return 0;
}*/

#include "Player.h"

int main() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	getGlobalNamespace(L)
		.beginClass<Character>("Character")
		.addConstructor<void(*)(void)>()
		.addProperty("name", &Character::getName, &Character::setName)
		.addFunction("say", &Character::say)
		.endClass()
		.deriveClass<Player, Character>("Player")
		.addProperty("hp", &Player::getHp, &Player::setHp)
		.addProperty("maxHp", &Player::getMaxHp, &Player::setMaxHp)
		.endClass();

	Player player;
	player.setName("Player");
	Character witch;
	witch.loadScript(L, "witch.lua", "witch");
	Character guard;
	guard.loadScript(L, "guard.lua", "guard");


	std::cout << "|Player walks around the town and talks with the witch and the guard!" << std::endl;
	witch.interact(&player);
	guard.interact(&player);

	std::cout << "|Player  accidentally hurts himself with a pair of scissors!" << std::endl;
	player.setHp(player.getHp() - 5);
	std::cout << "|Back to the town... Let's talk to the witch again!" << std::endl;
	witch.interact(&player);
	int apa;
	std::cin >> apa;
}