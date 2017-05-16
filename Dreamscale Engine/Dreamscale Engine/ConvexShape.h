#pragma once

#include <SFML\Graphics.hpp>
#include <string>

namespace dse
{
	class ConvexShape : public sf::ConvexShape
	{
	public:
		ConvexShape();
		~ConvexShape();

		std::string GetName() const;
		void SetName(std::string n);

	private:
		std::string name;
	};
}
