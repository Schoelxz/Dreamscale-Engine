#pragma once
#include "GameObject.h"
#include <vector>

namespace dse
{

	static class ObjectHandler
	{
	public:

		std::vector<GameObject*> getObject();
		void createNewObject();
		void destroyObject(GameObject* object);

		void getObjects(std::vector<GameObject*> objects);

		

		ObjectHandler();
		~ObjectHandler();

	private:
		std::vector<GameObject*> gameObject;
		
	};
}
