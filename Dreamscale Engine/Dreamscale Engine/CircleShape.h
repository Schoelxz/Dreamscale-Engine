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
		std::string GetType() const;
		bool GetVisible();
		void SetName(std::string n);
		void SetType(std::string t);
		void SetVisible(bool state);

	private:
		std::string name;
		std::string type;
		bool isAlive = true;
		bool isVisible = true;
	};
}
