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
	//Kevin's code
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
		std::map<std::string, Tmx::Map*> map_vector;

		TmxHandler();
		~TmxHandler();

		//Creates (but does not load) all Tmx::maps at start.
		void ParseAllMaps(); //Joel's code

		//Resets the object vector for the current map (used when a new map is loaded).
		void ResetVector(); //Kevin's code

		//Loads a Tmx::map
		void LoadMap(Tmx::Map* map); //Joel's code

		//Loads the current map's objects.
		void LoadObjects(const Tmx::Map& map); //Kevin and Daniel's code

		//Gets all the filenames in the given (parameter) directory.
		std::vector<std::string> GetTmxFilenamesInFolder(std::string folder); //Joel's code
		
		//Gets m_all_file_names.
		std::vector<std::string> GetTmxNames(); //Joel's code

		//Gets all drawable objects (For Lua Binding).
		std::vector<DrawableType*> GetDrawable() const; //Joel's code

		//Loops through all objects and updates them if their values are 
		//any different from the last time the functionwas called.
		void RefreshObjects(); //Kevin's code

		//Draws the current map.
		void DrawMap(sf::RenderWindow& window); //Joel's code

		//Draws the current maps' objects.
		void DrawObjects(sf::RenderWindow& window); //Kevin and Daniel's code

	private:
		int m_current_tileset; //For Loading Map.
		int m_map_index;

		Tmx::Map* m_tmx_map;

		std::map<int, DrawableType*> m_drawables;
		std::vector<sf::VertexArray*> m_vertex_layers;
		std::vector<dse::Sprite*> m_sprite_vector;
		std::vector<dse::RectangleShape*> m_rectangle_vector;
		std::vector<dse::CircleShape*> m_circle_vector;
		std::vector<dse::ConvexShape*> m_convex_vector;
		std::vector<DrawableType*> m_drawable;

		std::vector<sf::Texture*> m_tileset_textures;
		std::vector<sf::Texture*> m_sprite_textures;

		std::vector<std::string> m_all_tmx_filenames;

		//Sets a tile's texture and flips it accordingly.
		void SetTile(sf::Vertex* &quad, Tmx::MapTile tile, int i, int j,
			const sf::Vector2i tile_size, sf::Vector2i texture_coord); //Joel's code

		//Determines an objects shape (rectangle, circle, sprite, etc).
		void DetermineDrawableType(Tmx::Object& obj, const Tmx::Map& tmx_map); //Kevin and Daniel's code
	};
}
#endif