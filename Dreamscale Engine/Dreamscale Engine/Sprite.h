#pragma once
#include <SFML\Graphics.hpp>

namespace dse
{
	class Sprite : public sf::Sprite
	{
	public:
		Sprite();
		~Sprite();

		std::string GetName() const;
		std::string GetTag() const;
		bool GetVisible();
		void SetName(std::string n);
		void SetTag(std::string n);
		void SetVisible(bool state);

	private:
		std::string name;
		std::string tag;
		bool isAlive = true;
		bool isVisible = true;
	};
}
