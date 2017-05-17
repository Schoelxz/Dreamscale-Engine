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

std::string dse::Sprite::GetTag() const
{
	return std::string();
}

bool dse::Sprite::GetVisible()
{
	return isVisible;
}

void Sprite::SetName(std::string n)
{
	name = n;
}

void dse::Sprite::SetTag(std::string n)
{
}

void dse::Sprite::SetVisible(bool state)
{
	isVisible = state;
}