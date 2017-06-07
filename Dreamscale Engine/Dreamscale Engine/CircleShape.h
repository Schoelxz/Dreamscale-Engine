#ifndef DREAMSCALEENGINE_CIRCLESHAPE_H_
#define DREAMSCALEENGINE_CIRCLESHAPE_H_

#include <SFML\Graphics.hpp>
#include <string>

namespace dse
{
	//Kevin's code
	class CircleShape : public sf::CircleShape
	{
	public:
		CircleShape();
		~CircleShape();

		//Gets object's name
		std::string GetName() const;

		//Gets object's type
		std::string GetType() const;

		//Gets object's visibility
		bool GetVisible() const;

		//Gets object's position
		sf::Vector2f GetPosition() const;

		//Gets object's radius
		float GetRadius() const;

		//Sets object's name
		void SetName(std::string n);

		//Sets object's type
		void SetType(std::string t);

		//Sets object's visibility
		void SetVisible(bool state);

		//Sets object's position.
		void SetPosition(sf::Vector2f pos);

		//Sets object's radius.
		void SetRadius(float radius);

		//Lua testing
		static const std::vector<dse::CircleShape*> GetCircleshapeVector(); //Joel's code

	private:
		std::string m_name;
		std::string m_type;
		bool m_is_alive = true;
		bool m_is_visible = true;

		static std::vector<dse::CircleShape*> s_circleshape_vector; //Lua testing
	};
}
#endif