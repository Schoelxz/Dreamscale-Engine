#ifndef DREAMSCALEENGINE_SFMLOBJECT_H_
#define DREAMSCALEENGINE_SFMLOBJECT_H_

#include <iostream>
#include <memory>
#include <SFML\Graphics.hpp>
#include <lua.hpp>
#include <LuaBridge.h>

//Joel's code
class SfmlObject
{
public:
	sf::RectangleShape rect_shape;

	SfmlObject();
	SfmlObject(const std::string& name);
	~SfmlObject();

	//Function for finding this object in Lua.
	static SfmlObject* Find(const std::string instance_name);

	//Gets object's size.
	const sf::Vector2f GetSize() const;

	//Gets object's position.
	const sf::Vector2f GetPosition() const;

	//Gets object's name.
	const std::string GetInstanceName() const;

	//Gets a vector of all SfmlObject's.
	static const std::vector<SfmlObject*>& GetAllObjects();

	//Sets object's size.
	void SetSize(int x, int y);

	//Sets object's position.
	void SetPosition(int x, int y);

	//Draws all SfmlObject's.
	void Draw(sf::RenderWindow* window);

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;

	std::string m_instance_name;

	static std::vector<SfmlObject*> s_sfml_objects;
};
#endif