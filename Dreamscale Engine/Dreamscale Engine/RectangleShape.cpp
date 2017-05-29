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

std::string dse::RectangleShape::GetType() const
{
	return type;
}

bool dse::RectangleShape::GetVisible()
{
	return isVisible;
}

void RectangleShape::SetName(std::string n)
{
	name = n;
}

void dse::RectangleShape::SetType(std::string t)
{
	type = t;
}

void dse::RectangleShape::SetVisible(bool state)
{
	isVisible = state;
}