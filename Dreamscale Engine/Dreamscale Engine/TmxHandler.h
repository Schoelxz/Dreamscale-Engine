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
#include <map>

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

	/*
	\brief Refreshes all objects.
	Loops through all objects and updates them
	if they're different from the last update funtction \n
	Example:
	Bandit1 died which changed representive Sprite
	class to not be visible. So the next time
	UpdateObjects loops through bandit's sprite
	it will make bandit invisible.
		This function will only be called from GameEngine.
	*/
	void UpdateObjects();

	//Resources kinda..
	void ParseAllMaps();
	
	void LoadMap(Tmx::Map* map);
	void LoadObjects(const Tmx::Map& map)
	{
		for (int i = 0; i < drawable.size(); i++) { delete drawable[i]; }
		for (int i = 0; i < spriteTextures.size(); i++) { delete spriteTextures[i]; }
		for (int i = 0; i < spriteVector.size(); i++) { delete spriteVector[i]; }
		for (int i = 0; i < rectangleVector.size(); i++) { delete rectangleVector[i]; }
		for (int i = 0; i < circleVector.size(); i++) { delete circleVector[i]; }
		for (int i = 0; i < convexVector.size(); i++) { delete convexVector[i]; }

		drawable.clear();
		spriteTextures.clear();
		spriteVector.clear();
		rectangleVector.clear();
		circleVector.clear();
		convexVector.clear();

		int tempCurrentTileset;

		//const std::vector<Tmx::Tileset*> tmxTileSet = map.GetTilesets();
		const std::vector<Tmx::ObjectGroup*>& objLayers = map.GetObjectGroups(); //number of object layers


																				 //for each object layer
		for (auto objects : objLayers)
		{
			//for each object in the object layer
			for (auto object : objects->GetObjects())
			{
				DeterminePolygonType(*object, map);
			}
		}
	}
	void DrawMap(sf::RenderWindow& window);
	void DrawObjects(sf::RenderWindow& window);
	void ResetVector();

	void SetTile(sf::Vertex* &quad, Tmx::MapTile tile, int i, int j,
	const sf::Vector2i tileSize, sf::Vector2i textCoord); //Sets a tiles texture and flips it correct

	
	Tmx::Map* map2;
	std::map<std::string, Tmx::Map*> mapVector;

private:
	int currentTileset; //For Loading Map
	int mapIndex;

	std::map<int, DrawableType*> m_drawable;
	std::vector<sf::VertexArray*> vertexLayers;
	std::vector<dse::Sprite*> spriteVector;
	std::vector<dse::RectangleShape*> rectangleVector;
	std::vector<dse::CircleShape*> circleVector;
	std::vector<dse::ConvexShape*> convexVector;
	std::vector<DrawableType*> drawable;
	std::vector<sf::Texture*> tileSetTexture;
	std::vector<sf::Texture*> spriteTextures;

	void DeterminePolygonType(Tmx::Object& obj, const Tmx::Map& m);
	//TODO: Fast? Fråga om hjälp!
};

