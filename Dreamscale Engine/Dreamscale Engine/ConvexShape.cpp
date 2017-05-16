#include "ConvexShape.h"

using namespace dse;

ConvexShape::ConvexShape()
{
}

ConvexShape::~ConvexShape()
{
}

std::string dse::ConvexShape::GetName() const
{
	return name;
}

void dse::ConvexShape::SetName(std::string n)
{
	name = n;
}
