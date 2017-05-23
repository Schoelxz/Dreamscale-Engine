#include "SfmlObject.h"

std::vector<SfmlObject*> SfmlObject::sfmlObjects = std::vector<SfmlObject*>();

SfmlObject::SfmlObject()
{
	sfmlObjects.push_back(this);
}

SfmlObject::SfmlObject(const std::string& name)
	: SfmlObject()
{
	m_instanceName = name;
}

SfmlObject::~SfmlObject()
{
}

////void SfmlObject::LoadScript(lua_State * L, const std::string & scriptFileName, const std::string & tableName)
////{
////	using namespace luabridge;
////	if (luaL_dofile(L, scriptFileName.c_str()) == 0) {
////		LuaRef table = getGlobal(L, tableName.c_str());
////		if (table.isTable()) {
////	
////		}
////	}
////	else {
////		std::cout << "Error, can't open script!" << std::endl;
////	}
////}

void SfmlObject::SetSize(int x, int y)
{
	m_size.x = x;
	m_size.y = y;
	rectShape.setSize(m_size);
}

void SfmlObject::SetPosition(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
	rectShape.setPosition(m_pos);
}

sf::Vector2f SfmlObject::GetSize()
{
	return m_size;
}

sf::Vector2f SfmlObject::GetPosition()
{
	return m_pos;
}

SfmlObject* SfmlObject::Find(const std::string instanceName)
{
	
	for (int i = 0; i < sfmlObjects.size(); i++)
	{
		if(sfmlObjects[i]->GetInstanceName() == instanceName)
			return sfmlObjects[i];
	}

	std::cout << "Could not find " << instanceName << std::endl;
	//return nullptr;
	
}

std::string SfmlObject::GetInstanceName()
{
	return m_instanceName;
}

const std::vector<SfmlObject*>& SfmlObject::GetAllObjects()
{
	return sfmlObjects;
}



