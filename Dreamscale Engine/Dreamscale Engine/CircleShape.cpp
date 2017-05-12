#include "CircleShape.h"

using namespace dse;

CircleShape::CircleShape()
{
}


CircleShape::~CircleShape()
{
}

std::string dse::CircleShape::GetName() const
{
	return std::string();
}

void dse::CircleShape::SetName(std::string n)
{
	name = n;
}