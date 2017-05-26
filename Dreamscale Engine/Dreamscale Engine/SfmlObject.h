#pragma once

#include <iostream>
#include <memory>
#include <SFML\Graphics.hpp>
#include <lua.hpp>
#include <LuaBridge.h>

class SfmlObject
{
public:
	SfmlObject();
	~SfmlObject();

	SfmlObject(const std::string& name);

	//void LoadScript(lua_State* L, const std::string& scriptFileName, const std::string& tableName);

	void SetSize(int x, int y);
	void SetPosition(int x, int y);
	sf::Vector2f GetSize();
	sf::Vector2f GetPosition();

	//std::shared_ptr<luabridge::LuaRef> interactFunction;
	sf::RectangleShape rectShape;

	static SfmlObject* Find(const std::string instanceName);
	//TODO: Keep working on finding and using class instances for LUA
	std::string GetInstanceName();

	static const std::vector<SfmlObject*>& GetAllObjects();

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;

	std::string m_instanceName;

	static std::vector<SfmlObject*> sfmlObjects;
	static int s_test;
};

