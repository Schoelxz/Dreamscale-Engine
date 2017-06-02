#ifndef DREAMSCALEENGINE_CIRCLESHAPE_H_
#define DREAMSCALEENGINE_CIRCLESHAPE_H_

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
		void SetName(std::string);
		void SetType(std::string);
		void SetVisible(bool);
		void SetPosition(sf::Vector2f);
		void SetRadius(float);

		static const std::vector<dse::CircleShape*> GetCircleshapeVector();

	private:
		std::string m_name;
		std::string m_type;
		bool m_is_alive = true;
		bool m_is_visible = true;

		static std::vector<dse::CircleShape*> s_circleshape_vector;
	};
}
#endif