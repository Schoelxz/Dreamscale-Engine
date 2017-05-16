#include "RectangleShape.h"

using namespace dse;

RectangleShape::RectangleShape()
{
}


RectangleShape::~RectangleShape()
{
}

std::string RectangleShape::GetName() const
{
	return name;
}

void RectangleShape::SetName(std::string n)
{
	name = n;
}
