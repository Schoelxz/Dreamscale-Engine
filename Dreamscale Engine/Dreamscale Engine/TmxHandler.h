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

	//Does what it says
	std::vector<std::string> get_all_files_names_within_folder(std::string folder); //TODO Joel: Create path dir for tmx maps (a place designers put their .tmx files)
	std::vector<std::string> GetTmxNames() { return allFileNames; };
	//Resources kinda..
	void ParseAllMaps();
	//Map
	void LoadMap(Tmx::Map* map); //Only used inside GameEngine update/play?

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
	void RefreshObjects();


	
	void DrawMap(sf::RenderWindow& window);
	//Objects
	void LoadObjects(const Tmx::Map& map);
	void DrawObjects(sf::RenderWindow& window);

	void ResetVector();

	std::vector<DrawableType*> GetDrawable() const; //For Lua Binding (but TmxHandler is getting big. Should be alot in seperate class/classes)

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
	Tmx::Map* map2;

	//used for storing values gained from gafnwf-function.
	std::vector<std::string> allFileNames;

	void SetTile(sf::Vertex*& quad, Tmx::MapTile tile, int i, int j,
		const sf::Vector2i tileSize, sf::Vector2i textCoord); //Sets a tiles texture and flips it correct
	//TODO: Fast? Fråga om hjälp!

	void DeterminePolygonType(Tmx::Object& obj, const Tmx::Map& m);
	//TODO: Fast? Fråga om hjälp!

};
