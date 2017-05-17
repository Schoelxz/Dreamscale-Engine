#pragma once
#include <SFML\Graphics.hpp>

namespace dse
{
	class RectangleShape : public sf::RectangleShape
	{
	public:
		RectangleShape();
		~RectangleShape();

		std::string GetName() const;
		void SetName(std::string n);
		void SetVisible(bool state);
		bool GetVisible();

	private:
		std::string name;
		bool isAlive = true;
		bool isVisible = true;
	};
}