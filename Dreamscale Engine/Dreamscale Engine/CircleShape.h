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
		bool GetVisible() const;
		sf::Vector2f GetPosition() const;
		float GetRadius() const;
		void SetName(std::string n);
		void SetType(std::string t);
		void SetVisible(bool state);
		void SetPosition(sf::Vector2f pos);
		void SetRadius(float radius);

		static const std::vector<dse::CircleShape*> GetCircleshapeVector();

	private:
		std::string name;
		std::string type;
		bool isAlive = true;
		bool isVisible = true;

		static std::vector<dse::CircleShape*> circleshape_vector;
	};
}
