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

std::string dse::Sprite::GetType() const
{
	return std::string(type);
}

bool dse::Sprite::GetVisible()
{
	return isVisible;
}

void Sprite::SetName(std::string n)
{
	name = n;
}

void dse::Sprite::SetType(std::string t)
{
	type = t;
}

void dse::Sprite::SetVisible(bool state)
{
	isVisible = state;
}