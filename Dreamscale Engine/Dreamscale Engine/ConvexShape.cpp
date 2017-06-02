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
	return m_name;
}

std::string dse::ConvexShape::GetType() const
{
	return std::string();
}

bool dse::ConvexShape::GetVisible()
{
	return m_is_visible;
}

void ConvexShape::SetName(std::string n)
{
	m_name = n;
}

void dse::ConvexShape::SetType(std::string t)
{
	m_type = t;
}

void dse::ConvexShape::SetVisible(bool state)
{
	m_is_visible = state;
}
