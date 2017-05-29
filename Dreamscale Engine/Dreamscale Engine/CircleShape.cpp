#include "CircleShape.h"

std::vector<dse::CircleShape*> dse::CircleShape::circleshape_vector = std::vector<dse::CircleShape*>();

using namespace dse;

CircleShape::CircleShape()
{
	circleshape_vector.push_back(this);
}

CircleShape::~CircleShape()
{
}

std::string CircleShape::GetName() const
{
	return name;
}

std::string dse::CircleShape::GetType() const
{
	return type;
}

bool dse::CircleShape::GetVisible() const
{
	return isVisible;
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
	name = n;
}

void dse::CircleShape::SetType(std::string t)
{
	type = t;
}

void dse::CircleShape::SetVisible(bool state)
{
	isVisible = state;
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
	return circleshape_vector;
}
