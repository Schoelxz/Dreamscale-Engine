#include "CircleShape.h"

std::vector<dse::CircleShape*> dse::CircleShape::s_circleshape_vector = std::vector<dse::CircleShape*>();

using namespace dse;

CircleShape::CircleShape()
{
	s_circleshape_vector.push_back(this);
}

CircleShape::~CircleShape()
{
}

std::string CircleShape::GetName() const
{
	return m_name;
}

std::string dse::CircleShape::GetType() const
{
	return m_type;
}

bool dse::CircleShape::GetVisible() const
{
	return m_is_visible;
}

sf::Vector2f dse::CircleShape::GetPosition() const
{
	return getPosition();
}

float dse::CircleShape::GetRadius() const
{
	return getRadius();
}

void CircleShape::SetName(std::string n)
{
	m_name = n;
}

void dse::CircleShape::SetType(std::string t)
{
	m_type = t;
}

void dse::CircleShape::SetVisible(bool state)
{
	m_is_visible = state;
}

void dse::CircleShape::SetPosition(sf::Vector2f pos)
{
	setPosition(pos);
}

void dse::CircleShape::SetRadius(float radius)
{
	setRadius(radius);
}

const std::vector<dse::CircleShape*> dse::CircleShape::GetCircleshapeVector()
{
	return s_circleshape_vector;
}
