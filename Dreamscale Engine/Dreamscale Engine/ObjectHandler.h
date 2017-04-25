#pragma once
#include "GameObject.h"
#include <vector>

namespace dse
{

	static class ObjectHandler
	{
	public:

		//std::vector<GameObject*> getObject();
		void createNewObject();
		void destroyObject(GameObject* object);

		std::vector<GameObject*> gameObject;

		ObjectHandler();
		~ObjectHandler();

		
	};
}
