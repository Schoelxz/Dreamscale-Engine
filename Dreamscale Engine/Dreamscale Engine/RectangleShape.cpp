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

void dse::RectangleShape::SetVisible(bool state)
{
	isVisible = state;
}

bool dse::RectangleShape::GetVisible()
{
	return isVisible;
}