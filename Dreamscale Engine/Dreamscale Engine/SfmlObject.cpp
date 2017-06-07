#include "SfmlObject.h"

std::vector<SfmlObject*> SfmlObject::s_sfml_objects = std::vector<SfmlObject*>();

SfmlObject::SfmlObject()
{
	s_sfml_objects.push_back(this);
}

SfmlObject::SfmlObject(const std::string& name)
	: SfmlObject()
{
	m_instance_name = name;
}

SfmlObject::~SfmlObject()
{
}

SfmlObject* SfmlObject::Find(const std::string instance_name)
{
	for (int i = 0; i < s_sfml_objects.size(); i++)
	{
		if (s_sfml_objects[i]->GetInstanceName() == instance_name)
			return s_sfml_objects[i];
	}

	std::cout << "Could not find " << instance_name << std::endl;
	return nullptr;
}

const sf::Vector2f SfmlObject::GetSize() const
{
	return m_size;
}

const sf::Vector2f SfmlObject::GetPosition() const
{
	return m_pos;
}

const std::string SfmlObject::GetInstanceName() const
{
	return m_instance_name;
}

const std::vector<SfmlObject*>& SfmlObject::GetAllObjects()
{
	return s_sfml_objects;
}

void SfmlObject::SetSize(int x, int y)
{
	m_size.x = x;
	m_size.y = y;
	rect_shape.setSize(m_size);
}

void SfmlObject::SetPosition(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
	rect_shape.setPosition(m_pos);
}

void SfmlObject::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < s_sfml_objects.size(); i++)
	{
		window->draw(s_sfml_objects[i]->rect_shape);
	}
}