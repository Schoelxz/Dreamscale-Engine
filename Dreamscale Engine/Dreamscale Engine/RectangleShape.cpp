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
	return m_name;
}

std::string dse::RectangleShape::GetType() const
{
	return m_type;
}

bool dse::RectangleShape::GetVisible()
{
	return m_is_visible;
}

void RectangleShape::SetName(std::string n)
{
	m_name = n;
}

void dse::RectangleShape::SetType(std::string t)
{
	m_type = t;
}

void dse::RectangleShape::SetVisible(bool state)
{
	m_is_visible = state;
}