#include "TmxHandler.h"
#include "CircleShape.h"

#include <Tmx\TmxPolygon.h>
#include <Tmx\TmxEllipse.h>
#include <Tmx\TmxPolyline.h>
#include <Tmx\TmxObjectGroup.h>

#include <Tmx\TmxTileset.h>
#include <Tmx\TmxTileLayer.h>
#include <Tmx\TmxImage.h>
#include <Tmx\TmxTile.h>
#include <Tmx\TmxMapTile.h>

#include <cassert>
#include <iostream>
#include <array>

enum FLIPPED
{
	DIAGONAL,
	HORIZONTAL,
	VERTICAL,
	NONE,
};

TmxHandler::TmxHandler()
{
	
}

void TmxHandler::LoadMap()
{
	//Tmx map file loads.
	map.ParseFile("orthogonal-outside.tmx");
	//map.ParseFile("EmanuelHolm-DesertDwellersPort.tmx");

	const std::vector<Tmx::Tileset*>& tmxTileSetMap = map.GetTilesets();
	const std::vector<Tmx::TileLayer*>& tileLayers = map.GetTileLayers(); //number of tilelayers
	 //number of object layers

	FLIPPED flipped = NONE;

	for (size_t i = 0; i < tmxTileSetMap.size(); i++)
	{
		sf::Texture* tileset = new sf::Texture();
		tileSetTexture.push_back(tileset);
		if (!tileset->loadFromFile(tmxTileSetMap[i]->GetImage()->GetSource()))
		{
			assert(!"Couldn't load file!");
		}
	}

	// Get size for map and tiles
	const int height = map.GetHeight();
	const int width = map.GetWidth();
	const int tileHeight = map.GetTileHeight();
	const int tileWidth = map.GetTileWidth();

	for (auto layer : map.GetLayers()) {
		//for each tilelayer
		for (int t = 0; t < tileSetTexture.size(); t++)
		{
			// Create a new vertexarray, acting as a list of quads
			sf::VertexArray* vertexArray = new sf::VertexArray(sf::Quads, height * width * 4);
			vertexLayers.push_back(vertexArray);
			// For each tile in this layer...
			for (size_t i = 0; i < height; ++i)
			{
				for (size_t j = 0; j < width; ++j)
				{
					//vertexTile.push_back(new sf::VertexArray(sf::Quads, height * width * 4));
					// Get the tile, and check if it's part of a tileset
					if (layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_TILE) {
						Tmx::TileLayer* tLayer = static_cast<Tmx::TileLayer*>(layer);
						const Tmx::MapTile tile = tLayer->GetTile(j, i);
						if (tile.tilesetId == -1 || tile.tilesetId != t)
							continue;

						const int gid = tile.gid;

						/*std::cout << "tile.tilesetID: " << tile.tilesetId << std::endl;
						std::cout << "gid: " << gid << std::endl;*/

						//for (int i = tileSetTexture.size() - 1; i >= 0; i--)
						//{
						//	if (tmxTileSetMap[i]->GetFirstGid() > gid)
						//	{
						//		//currentVertexTile.push_back(i);
						//		currentTileset = i;
						//		continue;
						//	}
						//	//currentVertexTile.push_back(i);
						//	currentTileset = i;
						//	break;
						//}

						//std::cout << "currentTileset: " << currentTileset << std::endl;

						int real_id = gid - tmxTileSetMap[t]->GetFirstGid();
						
						//std::cout << currentTileset << ": currenttileset in vertex" << std::endl;

						// Get the current vertexlayer
						//sf::VertexArray* vertexLayer = *(vertexArray);
						// Get the current quad
						sf::Vertex* quad = &(*vertexArray)[(i * width + j) * 4];

						// Calculate texture coordinates, based on the tilenumer
						unsigned int tileNumber = tile.id;
						int tu = tileNumber % (tileSetTexture[t]->getSize().x / tileWidth);
						int tv = tileNumber / (tileSetTexture[t]->getSize().x / tileWidth);

						/*
						The form that we align the vertices in to build our quads
						0 --- 1
						|     |
						|     |
						3 --- 2
						*/

						// Position the vertices, as specified above
						quad[0].position = sf::Vector2f(j * tileWidth, i * tileHeight);
						quad[1].position = sf::Vector2f((j + 1) * tileWidth, i * tileHeight);
						quad[2].position = sf::Vector2f((j + 1) * tileWidth, (i + 1) * tileHeight);
						quad[3].position = sf::Vector2f(j * tileWidth, (i + 1) * tileHeight);

						// The default order to specify texture coordinates by.
						std::array<size_t, 4> texOrder = { 0, 1, 2, 3 };
						// Different order if the tile is flipped horizontally
						if (tile.flippedHorizontally && tile.flippedVertically)
							flipped = DIAGONAL;
						else if (tile.flippedHorizontally)
							flipped = HORIZONTAL;
						else if (tile.flippedVertically)
							flipped = VERTICAL;
						else
							flipped = NONE;

						switch (flipped)
						{
						case DIAGONAL:
							texOrder = { 2, 3, 0, 1 };
							break;
						case HORIZONTAL:
							texOrder = { 1, 0, 3, 2 };
							break;
						case VERTICAL:
							texOrder = { 3, 2, 1, 0 };
							break;
						case NONE:
							texOrder = { 0, 1, 2, 3 };
							break;
						default:
							break;
						}

						// Position the texture coordinates. Coordinates is specified in pixels, not 0-1
						quad[texOrder[0]].texCoords = sf::Vector2f(tu * tileWidth, tv * tileHeight);
						quad[texOrder[1]].texCoords = sf::Vector2f((tu + 1) * tileWidth, tv * tileHeight);
						quad[texOrder[2]].texCoords = sf::Vector2f((tu + 1) * tileWidth, (tv + 1) * tileHeight);
						quad[texOrder[3]].texCoords = sf::Vector2f(tu * tileWidth, (tv + 1) * tileHeight);
					}
				}
			}
		}
	}
	
//	std::cout << vertexTile.size();
}

void TmxHandler::LoadObjects()
{
	//Parse tmx file into Map map
	int tempCurrentTileset;

	const std::vector<Tmx::Tileset*> tmxTileSet = map.GetTilesets();
	const std::vector<Tmx::ObjectGroup*>& objLayers = map.GetObjectGroups(); //number of object layers

	// Get size for map and tiles
	const int height = map.GetHeight();
	const int width = map.GetWidth();
	const int tileHeight = map.GetTileHeight();
	const int tileWidth = map.GetTileWidth();

	const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
	const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
	const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

	//for each object layer
	for (auto objects : objLayers)
	{
		//int totalObjects = objLayers

		//for each object IN object layer
		for (auto object : objects->GetObjects())
		{
			spriteVector.push_back(new sf::Sprite);
			std::cout << spriteVector.size() << std::endl;

			const int gid = object->GetGid();
			DeterminePolygonType(*object);
			if (gid == 0)
				continue;

			for (int i = tmxTileSet.size() - 1; i >= 0; i--)
			{
				if (tmxTileSet[i]->GetFirstGid() > gid)
				{
					tempCurrentTileset = i;
					continue;
				}
				tempCurrentTileset = i;
				break;
			}

			std::cout << object->GetId();
			
			int real_id = gid - tmxTileSet[tempCurrentTileset]->GetFirstGid();
			

			std::cout << tempCurrentTileset << ": currenttileset in Objects" << std::endl;

			real_id &=	~(FLIPPED_HORIZONTALLY_FLAG |
							FLIPPED_VERTICALLY_FLAG |
							FLIPPED_DIAGONALLY_FLAG);

			int tu2 = real_id % (tileSetTexture[tempCurrentTileset]->getSize().x / tileWidth);
			int tv2 = real_id / (tileSetTexture[tempCurrentTileset]->getSize().x / tileWidth);


			sf::IntRect textureSource; //= Objectets 4 rektangel värden

			textureSource.left = tu2 * tileWidth;
			textureSource.top = tv2 * tileHeight;

			textureSource.width = tileWidth;
			textureSource.height = tileHeight;

			sf::Image* tempImg = new sf::Image();
			sf::Texture* tempTex = new sf::Texture();
					
			tempImg->loadFromFile(tmxTileSet[tempCurrentTileset]->GetImage()->GetSource());
			tempTex->loadFromImage(*tempImg, textureSource);

			spriteVector[spriteVector.size() - 1]->setPosition(object->GetX(), object->GetY() - object->GetHeight());
			spriteVector[spriteVector.size() - 1]->setTexture(*tempTex);
		}
	}
}

void TmxHandler::DrawMap(sf::RenderWindow& window)
{
	//Set textureState size
	/*while(textureState.size() < tileSetTexture.size())
	{
		textureState.push_back(new sf::RenderStates());
	}*/

	sf::RenderStates state;

	for (int i = 0; i < vertexLayers.size(); i++) {
		state.texture = tileSetTexture[i % tileSetTexture.size()];
		window.draw(*vertexLayers[i], state);
	}


/*	//For every tileset..
	for (int i = 0; i < tileSetTexture.size(); i++)
	{
		textureState[i]->texture = tileSetTexture[i];

		//for (auto j : vertexLayers)
		for (int j = 0; j < vertexTile.size(); j++)
		{
			// Render a vertexarray, with the custom renderstate
			window.draw(*vertexTile[j], *textureState[i]);
		}
	}*/
	
}

void TmxHandler::DrawObjects(sf::RenderWindow & window)
{
/*	//Draws all sprites inside the spriteVector
	for (int i = 0; i < spriteVector.size() - 1; i++)
	{
		window.draw(*spriteVector[i]);
	}
	*/
	for (int i = 0; i < drawable.size(); i++) {
		window.draw(*drawable[i]);
	}
}

//TODO: Do a representive dse::subclass of every sf::drawable (shape) class
void TmxHandler::DeterminePolygonType(Tmx::Object & obj)
{
	switch (obj.GetPrimitiveType())
	{
	case Tmx::TMX_PT_ELLIPSE: //circle
		{
			std::cout << " ellipse" << std::endl;
			dse::CircleShape *circle = new dse::CircleShape();
			circle->setRadius(obj.GetEllipse()->GetRadiusX());
			circle->setPosition(obj.GetX(), obj.GetY());
			circle->setFillColor(sf::Color(255, 255, 0, 64));
			circle->GetName();
			drawable.push_back(circle);
		}
		break;
	case Tmx::TMX_PT_POLYGON: //polygon
		{
			std::cout << " polygon" << std::endl;
			sf::ConvexShape *convex = new sf::ConvexShape();
			int numPoints = obj.GetPolygon()->GetNumPoints();
			convex->setPointCount(numPoints);
			for (int i = 0; i < numPoints; i++)
			{
				const sf::Vector2f pointPos = sf::Vector2f(obj.GetX() + obj.GetPolygon()->GetPoint(i).x, obj.GetY() + obj.GetPolygon()->GetPoint(i).y);
				convex->setPoint(i, pointPos);
			}
			convex->setFillColor(sf::Color(0, 0, 255, 64));

			drawable.push_back(convex);
		}
		break;
	case Tmx::TMX_PT_POLYLINE: //polyline
		{
			std::cout << " polyline" << std::endl;
			
			sf::VertexArray* vertex = new sf::VertexArray(sf::LineStrip, obj.GetPolyline()->GetNumPoints());
			int numPoints = obj.GetPolyline()->GetNumPoints();
			for (int i = 0; i < numPoints; i++)
			{
				const sf::Vector2f pointPos = sf::Vector2f(obj.GetX() + obj.GetPolyline()->GetPoint(i).x, obj.GetY() + obj.GetPolyline()->GetPoint(i).y);
				(*vertex)[i].position = pointPos;
				(*vertex)[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
			}
			drawable.push_back(vertex);
		}
		break;
	case Tmx::TMX_PT_NONE:
		{
			if (obj.GetGid() == 0) //rectangle
			{
				std::cout << "rect" << std::endl;
				sf::RectangleShape *rectangle = new sf::RectangleShape();
				rectangle->setSize(sf::Vector2f(obj.GetWidth(), obj.GetHeight()));
				rectangle->setPosition(obj.GetX(), obj.GetY());
				rectangle->setFillColor(sf::Color(0, 255, 0, 64));
				drawable.push_back(rectangle);
			}
			else //tileObject
			{
				std::cout << "tile" << std::endl;
			}
			//std::cout << " something went wrong" << std::endl;
		}
		break;
	default:
		break;
	}
}
