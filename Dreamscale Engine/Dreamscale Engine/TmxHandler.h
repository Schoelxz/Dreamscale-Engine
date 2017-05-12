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

#include <string>
#include <Windows.h>

//For rendering every layer
#include <SFML\Graphics.hpp>

class TmxHandler
{
public:
	TmxHandler();

	//Does what it says
	std::vector<std::string> get_all_files_names_within_folder(std::string folder);
	//used for getting above function's values.
	std::vector<std::string> allFileNames;

	//Resources kinda..
	void ParseAllMaps();
	void LoadAllTilesets();
	//\\

	void LoadMap(Tmx::Map* map);
	void LoadObjects(Tmx::Map& map);
	void DrawMap(sf::RenderWindow& window);
	void DrawObjects(sf::RenderWindow& window);
	
	void SetTile(
		sf::Vertex* &quad,
		Tmx::MapTile tile,
		int i, int j,
		const sf::Vector2i tileSize,
		sf::Vector2i textCoord
		); //Sets a tiles texture and flips it correct


	Tmx::Map* map2;
	std::map<std::string, Tmx::Map*> mapVector;
private:
	//TODO: Skapa en vector av map för att kunna ladda in flera tmx filer
	//Trouble to create map as a pointer, gave weird error to a another library class.


	std::vector<sf::VertexArray*> vertexLayers;
	std::vector<sf::Sprite*> spriteVector;

	// Load the texture specifying the tileset
	std::vector<sf::Texture*> tileSetTexture;

	std::vector<sf::Texture*> spriteTextures;

	int currentTileset; //For Loading Map

	//TODO: Fast? Fråga om hjälp!
};

