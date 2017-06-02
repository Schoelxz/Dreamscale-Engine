#ifndef DREAMSCALEENGINE_RECTANGLESHAPE_H_
#define DREAMSCALEENGINE_RECTANGLESHAPE_H_


#include <SFML\Graphics.hpp>
#include <string>

namespace dse
{
	class RectangleShape : public sf::RectangleShape
	{
	public:
		RectangleShape();
		~RectangleShape();

		std::string GetName() const;
		std::string GetType() const;
		bool GetVisible();
		void SetName(std::string);
		void SetType(std::string);
		void SetVisible(bool);

	private:
		std::string m_name;
		std::string m_type;
		bool m_is_alive = true;
		bool m_is_visible = true;
	};
}
#endif