#pragma once
//For handling TMX files
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObject.h>

//For rendering every layer
#include <SFML\Graphics.hpp>

class TmxHandler
{
public:
	TmxHandler();

	void LoadMap();
	void LoadObjects();
	void DrawMap(sf::RenderWindow& window);
	void DrawObjects(sf::RenderWindow& window);

//private:
	Tmx::Map map;

	void DeterminePolygonType(Tmx::Object& obj);

	// Create a non-default renderstate, and bind our tileset texture to it
	//std::vector<sf::RenderStates*> textureState;

	//std::vector<int> currentVertexTile;
	//std::vector<sf::VertexArray*> vertexTile;
	std::vector<sf::VertexArray*> vertexLayers;
	std::vector<sf::Sprite*> spriteVector;
	std::vector<sf::Drawable*> drawable;

	// Load the texture specifying the tileset
	std::vector<sf::Texture*> tileSetTexture;

	int currentTileset; //For Loading Map

};

