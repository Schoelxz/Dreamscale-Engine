#ifndef DREAMSCALEENGINE_CONVEXSHAPE_H_
#define DREAMSCALEENGINE_CONVEXSHAPE_H_

#include <SFML\Graphics.hpp>
#include <string>

namespace dse
{
	//Kevin's code
	class ConvexShape : public sf::ConvexShape
	{
	public:
		ConvexShape();
		~ConvexShape();

		//Gets object's name
		std::string GetName() const;

		//Gets object's type
		std::string GetType() const;

		//Gets object's visibility
		bool GetVisible();

		//Sets object's name
		void SetName(std::string n);

		//Sets object's type
		void SetType(std::string t);

		//Sets object's visibility
		void SetVisible(bool state);

	private:
		std::string m_name;
		std::string m_type;
		bool m_is_alive = true;
		bool m_is_visible = true;
	};
}
#endif