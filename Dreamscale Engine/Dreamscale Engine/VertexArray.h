#pragma once

#include <SFML\Graphics.hpp>
#include <string>

namespace dse
{
	class VertexArray : public sf::VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		std::string GetName() const;
		void SetName(std::string n);

	private:
		std::string name;
	};
}