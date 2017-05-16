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

void VertexArray::SetName(std::string n)
{
	name = n;
}
