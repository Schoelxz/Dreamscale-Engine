#ifndef DREAMSCALEENGINE_SPRITE_H_
#define DREAMSCALEENGINE_SPRITE_H_

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
		void SetName(std::string);
		void SetType(std::string);
		void SetScript();
		void SetVisible(bool state);

	private:
		std::string m_name;
		std::string m_type;
		std::string m_script;
		bool m_is_alive = true;
		bool m_is_visible = true;
	};
}
#endif