#pragma once

#include <SFML\Graphics.hpp>
#include <string>

namespace dse
{
	class Sprite : public sf::Sprite
	{
	public:
		Sprite();
		~Sprite();

		std::string GetName() const;
		std::string GetType() const;
		std::string GetScript() const;
		bool GetVisible();
		void SetName(std::string n);
		void SetType(std::string t);
		void setScript();
		void SetVisible(bool state);

	private:
		std::string name;
		std::string type;
		std::string script;
		bool isAlive = true;
		bool isVisible = true;
	};
}
