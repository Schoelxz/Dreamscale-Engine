#pragma once
//For handling TMX files
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObjectGroup.h>
#include <Tmx\TmxObject.h>
#include <Tmx\TmxTileset.h>
#include <Tmx\TmxTileLayer.h>
#include <Tmx\TmxImage.h>
#include <Tmx\TmxTile.h>
#include <Tmx\TmxMapTile.h>

#include <cassert>
#include <iostream>
#include <array>

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

	void CheckYPosition(sf::Sprite object);

//private:
	Tmx::Map map;

	std::vector<sf::VertexArray*> vertexLayers;
	std::vector<sf::Sprite*> spriteVector;

	// Load the texture specifying the tileset
	std::vector<sf::Texture*> tileSetTexture;

	int currentTileset;

};

