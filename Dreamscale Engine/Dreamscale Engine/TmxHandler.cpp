#include "TmxHandler.h"

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

	const std::vector<Tmx::Tileset*> tmxTileSet = map.GetTilesets();
	const std::vector<Tmx::TileLayer*>& tileLayers = map.GetTileLayers(); //number of tilelayers
	 //number of object layers

	FLIPPED flipped = NONE;

	for (size_t i = 0; i <= tmxTileSet.size() - 1; i++)
	{
		tileSetTexture.push_back(new sf::Texture());
		if (!tileSetTexture[i]->loadFromFile(tmxTileSet[i]->GetImage()->GetSource()))
		{
			assert(!"Couldn't load file!");
		}
	}

	// Get size for map and tiles
	const int height = map.GetHeight();
	const int width = map.GetWidth();
	const int tileHeight = map.GetTileHeight();
	const int tileWidth = map.GetTileWidth();

	


	//for each tilelayer
	for (auto tiles : tileLayers)
	{
		// Create a new vertexarray, acting as a list of quads
		vertexLayers.push_back(new sf::VertexArray(sf::Quads, height * width * 4));

		// For each tile in this layer...
		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j)
			{
				// Get the tile, and check if it's part of a tileset
				const Tmx::MapTile tile = tiles->GetTile(j, i);


				const int gid = tile.gid;
				//std::cout << tileSetTexture.size() << tmxTileSet.size();

				for (int i = tileSetTexture.size() - 1; i >= 0; i--)
				{
					if (tmxTileSet[i]->GetFirstGid() > gid)
					{
						currentTileset = i;
						continue;
					}
					currentTileset = i;
					break;
				}
				int real_id = gid - tmxTileSet[currentTileset]->GetFirstGid();

				if (tile.tilesetId == -1)
					continue;

				std::cout << currentTileset << ": currenttileset in vertex" << std::endl;

				// Get the currect vertexlayer
				sf::VertexArray* vertexLayer = *(vertexLayers.end() - 1);
				// Get the current quad
				sf::Vertex* quad = &(*vertexLayer)[(i * width + j) * 4];

				// Calculate texture coordinates, based on the tilenumer
				unsigned int tileNumber = tile.id;
				int tu = tileNumber % (tileSetTexture[currentTileset]->getSize().x / tileWidth);
				int tv = tileNumber / (tileSetTexture[currentTileset]->getSize().x / tileWidth);

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

void TmxHandler::LoadObjects()
{
	//Parse tmx file into Map map
	int tempCurrentTileset;

	const std::vector<Tmx::Tileset*> tmxTileSet = map.GetTilesets();
	const std::vector<Tmx::ObjectGroup*>& objLayers = map.GetObjectGroups(); //number of object layers

	for (size_t i = 0; i <= tmxTileSet.size() - 1; i++)
	{
		tileSetTexture.push_back(new sf::Texture());
		if (!tileSetTexture[i]->loadFromFile(tmxTileSet[i]->GetImage()->GetSource()))
		{
			assert(!"Couldn't load file!");
		}
	}

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
			if (object->GetType() == "rectangle")
			{
				std::cout << object->GetName() << " ";
				std::cout << "rectangle!" << std::endl;
			}
			if (object->GetType() == "polygon")
			{
				std::cout << object->GetName() << " ";
				std::cout << "polygon!" << std::endl;
			}
			if (object->GetType() == "polyline")
			{
				std::cout << object->GetName() << " ";
				std::cout << "polyline!" << std::endl;
			}
			if (object->GetType() == "elipse")
			{
				std::cout << object->GetName() << " ";
				std::cout << "elipse!" << std::endl;
			}
			else
			{
				std::cout << "tile object" << std::endl;
			}

			spriteVector.push_back(new sf::Sprite);
			//std::cout << spriteVector.size() << std::endl;

			const int gid = object->GetGid();

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

			int real_id = gid - tmxTileSet[tempCurrentTileset]->GetFirstGid();
			if (real_id == -1)
				continue;

			//std::cout << tempCurrentTileset << ": currenttileset in Objects" << std::endl;

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
	// Create a non-default renderstate, and bind our tileset texture to it
	sf::RenderStates states;
	states.texture = tileSetTexture[currentTileset];
	for (auto i : vertexLayers)
	{
		// Render a vertexarray, with the custom renderstate
		window.draw(*i, states);
	}
}

void TmxHandler::DrawObjects(sf::RenderWindow & window)
{
	//Draws all sprites inside the spriteVector
	for (int i = 0; i < spriteVector.size() - 1; i++)
	{
		window.draw(*spriteVector[i]);
	}
}

const sf::Sprite & TmxHandler::GetObjects(int index)
{
	return *spriteVector[index];
}

//void TmxHandler::SetObjectType()
//{
//	for (int i = 0; i < spriteVector.size(); i++)
//	{
//
//	}
//}