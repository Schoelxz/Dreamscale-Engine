#include "Sprite.h"

using namespace dse;

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

std::string Sprite::GetName() const
{
	return name;
}

void Sprite::SetName(std::string n)
{
	name = n;
}
