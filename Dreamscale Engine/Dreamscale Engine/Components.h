#ifndef DSE_COMPONENTS_H
#define DSE_COMPONENTS_H
#include <SFML\Graphics.hpp>
namespace dse
{
	typedef struct
	{
	private:
		float x, y;
	public:
		sf::Vector2f getPosition()
		{
			return sf::Vector2f(x, y);
		}
		sf::Vector2f setPosition(float xPos, float yPos)
		{
			x = xPos;
			y = yPos;
			return sf::Vector2f(x, y);
		}

	}Position;

	typedef struct
	{
	private:
		float angle;
	public:
		float setRotation(float rotValue)
		{
			angle = rotValue;
			return angle;
		}
		float getRotation()
		{
			return angle;
		}

	}Rotation;

	typedef struct
	{
	private:
		float x, y;
	public:
		sf::Vector2f getScale()
		{
			return sf::Vector2f(x, y);
		}
		sf::Vector2f setScale(float xScale, float yScale)
		{
			x = xScale;
			y = yScale;
			return sf::Vector2f(x, y);
		}

	}Scale;

	typedef struct   
	{
	public:
		Position position;
		Rotation rotation;
		Scale scale;
	}Transform;

}

#endif
