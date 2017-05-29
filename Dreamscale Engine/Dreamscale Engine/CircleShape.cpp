#include "CircleShape.h"

using namespace dse;

CircleShape::CircleShape()
{
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
	return std::string();
}

bool dse::CircleShape::GetVisible()
{
	return isVisible;
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