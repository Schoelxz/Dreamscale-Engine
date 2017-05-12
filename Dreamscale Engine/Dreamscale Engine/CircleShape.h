#pragma once

#include <SFML\Graphics.hpp>
#include <string>

namespace dse
{
	class CircleShape : public sf::CircleShape
	{
	public:
		CircleShape();
		~CircleShape();

		std::string GetName() const;
		void SetName(std::string n);

	private:
		std::string name;
	};
}
