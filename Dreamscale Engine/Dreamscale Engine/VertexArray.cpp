#include "VertexArray.h"

using namespace dse;

VertexArray::VertexArray()
{
}

VertexArray::~VertexArray()
{
}

std::string VertexArray::GetName() const
{
	return m_name;
}

std::string dse::VertexArray::GetType() const
{
	return std::string();
}

bool dse::VertexArray::GetVisible()
{
	return m_is_visible;
}

void VertexArray::SetName(std::string n)
{
	m_name = n;
}

void dse::VertexArray::SetType(std::string t)
{
	m_type = t;
}

void dse::VertexArray::SetVisible(bool state)
{
	m_is_visible = state;
}
