#pragma once

#include <memory>
#include <string>
#include <lua.hpp>
#include <LuaBridge.h>

class Character {
public:
	Character();
	void loadScript(lua_State* L, const std::string& scriptFilename,
		const std::string& tableName);
	virtual ~Character();
	void say(const std::string& text);
	std::string getName() const { return name; }
	void setName(const std::string& name) { this->name = name; }
	void interact(Character* character);
protected:
	std::string name;
	std::shared_ptr<luabridge::LuaRef> interactFunc;
};