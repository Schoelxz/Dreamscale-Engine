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
		void SetName(std::string n);

	private:
		std::string name;
	};
}
