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

void CircleShape::SetName(std::string n)
{
	name = n;
}