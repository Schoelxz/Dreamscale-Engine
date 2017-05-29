#include "ConvexShape.h"

using namespace dse;

ConvexShape::ConvexShape()
{
}

ConvexShape::~ConvexShape()
{
}

std::string ConvexShape::GetName() const
{
	return name;
}

std::string dse::ConvexShape::GetType() const
{
	return std::string();
}

bool dse::ConvexShape::GetVisible()
{
	return isVisible;
}

void ConvexShape::SetName(std::string n)
{
	name = n;
}

void dse::ConvexShape::SetType(std::string t)
{
	type = t;
}

void dse::ConvexShape::SetVisible(bool state)
{
	isVisible = state;
}
