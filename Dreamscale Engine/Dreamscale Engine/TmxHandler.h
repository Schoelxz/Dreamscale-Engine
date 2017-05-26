#pragma once
//For handling TMX files
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObject.h>

#include <string>
#include <Windows.h>

#include "CircleShape.h"

#include <Tmx\TmxPolygon.h>
#include <Tmx\TmxEllipse.h>
#include <Tmx\TmxPolyline.h>
#include <Tmx\TmxObjectGroup.h>
#include <Tmx\TmxMapTile.h>
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

enum FLIPPED
{
	DIAGONAL,
	HORIZONTAL,
	VERTICAL,
	NONE,
};

struct DrawableType
{
	enum Type {
		CIRCLE_SHAPE,
		CONVEX_SHAPE,
		RECTANGLE_SHAPE,

		SPRITE,
		TEXT,
		VERTEX_ARRAY
	};

	Type t;
	sf::Drawable* d;

	sf::CircleShape* GetCircleShape() const
	{
		return static_cast<sf::CircleShape*>(d);
	}
	sf::ConvexShape* GetConvexShape() const
	{
		return static_cast<sf::ConvexShape*>(d);
	}
	sf::RectangleShape* GetRectangleShape() const
	{
		return static_cast<sf::RectangleShape*>(d);
	}
	sf::Sprite* GetSprite() const
	{
		return static_cast<sf::Sprite*>(d);
	}

	DrawableType(Type _t, sf::Drawable* _d)
	{
		t = _t;
		d = _d;
	}
};

class TmxHandler
{
public:
	TmxHandler();

	//Does what it says
	std::vector<std::string> get_all_files_names_within_folder(std::string folder); //TODO Joel: Create path dir for tmx maps (a place designers put their .tmx files)
	std::vector<std::string> GetTmxNames() { return allFileNames; };
	//Resources kinda..
	void ParseAllMaps();
	//Map
	void LoadMap(Tmx::Map* map); //Only used inside GameEngine update/play?
	void DrawMap(sf::RenderWindow& window);
	//Objects
	void LoadObjects(Tmx::Map* map);
	void DrawObjects(sf::RenderWindow& window);

	std::map<std::string, Tmx::Map*> mapVector;
private:
	int currentTileset; //For Loading Map
	std::vector<sf::VertexArray*> vertexLayers;
	std::vector<sf::Sprite*> spriteVector;
	std::vector<sf::RectangleShape*> rectangleVector;
	std::vector<dse::CircleShape*> circleVector;
	std::vector<sf::ConvexShape*> convexVector;
	std::vector<DrawableType*> drawable;
	std::vector<sf::Texture*> tileSetTexture;
	std::vector<sf::Texture*> spriteTextures;
	Tmx::Map* map2;

	//used for storing values gained from gafnwf-function.
	std::vector<std::string> allFileNames;

	void DeterminePolygonType(Tmx::Object& obj, Tmx::Map& m);

	void SetTile(sf::Vertex*& quad, Tmx::MapTile tile, int i, int j,
		const sf::Vector2i tileSize, sf::Vector2i textCoord); //Sets a tiles texture and flips it correct
	//TODO: Fast? Fråga om hjälp!

};
