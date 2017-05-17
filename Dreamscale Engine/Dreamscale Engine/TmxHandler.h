#pragma once
//For handling TMX files
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObject.h>

#include <string>
#include <Windows.h>

#include "CircleShape.h"
#include "RectangleShape.h"
#include "VertexArray.h"
#include "ConvexShape.h"
#include "Sprite.h"

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

	dse::CircleShape* GetCircleShape() const
	{
		return static_cast<dse::CircleShape*>(d);
	}
	dse::ConvexShape* GetConvexShape() const
	{
		return static_cast<dse::ConvexShape*>(d);
	}
	dse::RectangleShape* GetRectangleShape() const
	{
		return static_cast<dse::RectangleShape*>(d);
	}
	dse::Sprite* GetSprite() const
	{
		return static_cast<dse::Sprite*>(d);
	}
	dse::VertexArray* GetVertexShape() const
	{
		return static_cast<dse::VertexArray*>(d);
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

	std::vector<std::string> get_all_files_names_within_folder(std::string folder);
	//used for getting above function's values.
	std::vector<std::string> allFileNames;

	//Resources kinda..
	void ParseAllMaps();

	void LoadMap(Tmx::Map* map);
	void LoadObjects(Tmx::Map& map);
	void DrawMap(sf::RenderWindow& window);
	void DrawObjects(sf::RenderWindow& window);
	
	void SetTile(sf::Vertex* &quad, Tmx::MapTile tile, int i, int j,
		const sf::Vector2i tileSize, sf::Vector2i textCoord); //Sets a tiles texture and flips it correct

	Tmx::Map* map2;
	std::map<std::string, Tmx::Map*> mapVector;

private:
	int currentTileset; //For Loading Map
	std::vector<sf::VertexArray*> vertexLayers;
	std::vector<dse::Sprite*> spriteVector;
	std::vector<dse::RectangleShape*> rectangleVector;
	std::vector<dse::CircleShape*> circleVector;
	std::vector<dse::ConvexShape*> convexVector;
	std::vector<DrawableType*> drawable;
	std::vector<sf::Texture*> tileSetTexture;
	std::vector<sf::Texture*> spriteTextures;

	void DeterminePolygonType(Tmx::Object& obj, Tmx::Map& m);
	//TODO: Fast? Fråga om hjälp!
};

