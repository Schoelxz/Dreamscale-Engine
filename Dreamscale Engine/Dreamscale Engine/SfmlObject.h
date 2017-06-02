#ifndef DREAMSCALEENGINE_SFMLOBJECT_H_
#define DREAMSCALEENGINE_SFMLOBJECT_H_

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

	SfmlObject(const std::string&);

	void SetSize(int, int);
	void SetPosition(int, int);
	const sf::Vector2f GetSize() const;
	const sf::Vector2f GetPosition() const;

	sf::RectangleShape rect_shape;

	void Draw(sf::RenderWindow*);

	static SfmlObject* Find(const std::string);

	const std::string GetInstanceName() const;

	static const std::vector<SfmlObject*>& GetAllObjects();

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;

	std::string m_instance_name;

	static std::vector<SfmlObject*> s_sfml_objects;
};

#endif