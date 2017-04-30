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
	void LoadMap();

private:
	Tmx::Map map;
	const Tmx::Tileset* tmxTileSet = *map.GetTilesets().begin();
	const Tmx::ObjectGroup* objGroup = *map.GetObjectGroups().begin();
	const std::vector<Tmx::TileLayer*>& tileLayers = map.GetTileLayers(); //number of tilelayers
	const std::vector<Tmx::ObjectGroup*>& objLayers = map.GetObjectGroups(); //number of object layers
	std::vector<sf::VertexArray*> vertexLayers;
	sf::Sprite sprObj;
	std::vector<Tmx::Object*> objs;
	std::vector<int> objId;
	std::vector<sf::Sprite*> spriteVector;

	sf::Texture objTex;
	// Load the texture specifying the tileset
	sf::Texture tileSet;


};

