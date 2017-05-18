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
	return name;
}

std::string dse::VertexArray::GetType() const
{
	return std::string();
}

bool dse::VertexArray::GetVisible()
{
	return isVisible;
}

void VertexArray::SetName(std::string n)
{
	name = n;
}

void dse::VertexArray::SetType(std::string t)
{
	type = t;
}

void dse::VertexArray::SetVisible(bool state)
{
	isVisible = state;
}
