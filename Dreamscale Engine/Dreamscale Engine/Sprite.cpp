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
	return m_name;
}

std::string dse::Sprite::GetType() const
{
	return m_type;
}

bool dse::Sprite::GetVisible()
{
	return m_is_visible;
}

void Sprite::SetName(std::string n)
{
	m_name = n;
}

void dse::Sprite::SetType(std::string t)
{
	m_type = t;
}

void dse::Sprite::SetVisible(bool state)
{
	m_is_visible = state;
}