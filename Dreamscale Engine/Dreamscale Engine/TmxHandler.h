#ifndef DREAMSCALEENGINE_TMXHANDLER_H_
#define DREAMSCALEENGINE_TMXHANDLER_H_

#include <string>
#include <Windows.h>
#include <cassert>
#include <iostream>
#include <array>
#include <map>

//For handling TMX files
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObject.h>
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

//For rendering
#include <SFML\Graphics.hpp>

#include "CircleShape.h"
#include "RectangleShape.h"
#include "VertexArray.h"
#include "ConvexShape.h"
#include "Sprite.h"

enum FLIPPED
{
	DIAGONAL,
	HORIZONTAL,
	VERTICAL,
	NONE,
};

namespace dse
{
	struct DrawableType
	{
		enum Type
		{
			CIRCLE_SHAPE,
			CONVEX_SHAPE,
			RECTANGLE_SHAPE,
			SPRITE,
			TEXT,
			VERTEX_ARRAY
		};

		Type type;
		sf::Drawable* drawable;

		dse::CircleShape* GetCircleShape() const
		{
			return static_cast<dse::CircleShape*>(drawable);
		}
		dse::ConvexShape* GetConvexShape() const
		{
			return static_cast<dse::ConvexShape*>(drawable);
		}
		dse::RectangleShape* GetRectangleShape() const
		{
			return static_cast<dse::RectangleShape*>(drawable);
		}
		dse::Sprite* GetSprite() const
		{
			return static_cast<dse::Sprite*>(drawable);
		}
		dse::VertexArray* GetVertexShape() const
		{
			return static_cast<dse::VertexArray*>(drawable);
		}

		DrawableType(Type _type, sf::Drawable* _drawable)
		{
			type = _type;
			drawable = _drawable;
		}
	};

	class TmxHandler
	{
	public:
		TmxHandler();

		std::vector<std::string> GetFileNamesInDir(std::string);
		std::vector<std::string> GetTmxNames() { return m_all_file_names; };
		void ParseAllMaps();
		//Map
		void LoadMap(Tmx::Map*); //Only used inside GameEngine update/play?

		//\brief Refreshes all objects.
		//Loops through all objects and updates them
		//if they're different from the last update funtction \n
		//Example:
		//Bandit1 died which changed representive Sprite
		//class to not be visible. So the next time
		//UpdateObjects loops through bandit's sprite
		//it will make bandit invisible.
		//		This function will only be called from GameEngine.
		void RefreshObjects();

		void DrawMap(sf::RenderWindow&);

		//Objects
		void LoadObjects(const Tmx::Map&);
		void DrawObjects(sf::RenderWindow&);

		void ResetVector();

		std::vector<DrawableType*> GetDrawable() const; //For Lua Binding (but TmxHandler is getting big. Should be alot in seperate class/classes)

		std::map<std::string, Tmx::Map*> map_vector;

	private:
		int m_current_tileset; //For Loading Map
		int m_map_index;

		std::map<int, DrawableType*> m_drawables;
		std::vector<sf::VertexArray*> m_vertex_layers;
		std::vector<dse::Sprite*> m_sprite_vector;
		std::vector<dse::RectangleShape*> m_rectangle_vector;
		std::vector<dse::CircleShape*> m_circle_vector;
		std::vector<dse::ConvexShape*> m_convex_vector;
		std::vector<DrawableType*> m_drawable;

		std::vector<sf::Texture*> m_tileset_textures;
		std::vector<sf::Texture*> m_sprite_textures;

		Tmx::Map* m_tmx_map;

		//used for storing values gained from gafnwf-function.
		std::vector<std::string> m_all_file_names;

		void SetTile(sf::Vertex*&, Tmx::MapTile, int, int,
			const sf::Vector2i, sf::Vector2i); //Sets a tiles texture and flips it correct

		void DeterminePolygonType(Tmx::Object&, const Tmx::Map&);
	};
}
#endif