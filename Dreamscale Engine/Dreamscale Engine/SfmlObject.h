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

	//void LoadScript(lua_State* L, const std::string& scriptFileName, const std::string& tableName);

	void SetSize(int x, int y);
	void SetPosition(int x, int y);
	sf::Vector2f GetSize();
	sf::Vector2f GetPosition();

	//std::shared_ptr<luabridge::LuaRef> interactFunction;
	sf::RectangleShape rectShape;

	SfmlObject* Find() const;

	static const std::vector<SfmlObject*>& GetAllObjects();

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;

	static std::vector<SfmlObject*> sfmlObjects;
};

