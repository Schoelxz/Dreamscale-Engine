#include "Character.h"
#include <iostream>
#include "Player.h"

Character::Character() : interactFunc(nullptr) {
}

Character::~Character() {
}

void Character::loadScript(lua_State* L, const std::string& scriptFilename, const std::string& tableName) {
	using namespace luabridge;
	if (luaL_dofile(L, scriptFilename.c_str()) == 0) {
		LuaRef table = getGlobal(L, tableName.c_str());
		if (table.isTable()) {
			if (table["name"].isString()) {
				name = table["name"].cast<std::string>();
			}
			else {
				name = "Null";
			}

			if (table["interact"].isFunction()) {
				interactFunc = std::make_shared<LuaRef>(table["interact"]);
			}
			else {
				interactFunc.reset();
			}
		}
	}
	else {
		std::cout << "Error, can't open script!" << std::endl;
	}
}

void Character::say(const std::string& text) {
	std::cout << name << ": " << text << std::endl;
}

void Character::interact(Character* character) {
	//Default to interact with player
	Player* p = static_cast<Player*>(character);

	// If p != nullptr, we know what we're interacting with a player! If not, do some other type of interaction
	if (interactFunc && p) {
		try {
			(*interactFunc)(this, p);
		}
		catch (luabridge::LuaException const& e) {
			std::cout << "LuaException: " << e.what() << std::endl;
		}
	}
}