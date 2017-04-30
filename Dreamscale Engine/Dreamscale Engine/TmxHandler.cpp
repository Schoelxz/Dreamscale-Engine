#include "TmxHandler.h"

enum FLIPPED
{
	DIAGONAL,
	HORIZONTAL,
	VERTICAL,
	NONE,
};

void TmxHandler::LoadMap()
{
	Tmx::Map map;

	map.ParseFile("orthogonal-outside.tmx");

	FLIPPED flipped = NONE;

	if (!tileSet.loadFromFile(tmxTileSet->GetImage()->GetSource()))
	{
		assert(!"Couldn't load file!");
	}

	// Get size for map and tiles
	const int height = map.GetHeight();
	const int width = map.GetWidth();
	const int tileHeight = map.GetTileHeight();
	const int tileWidth = map.GetTileWidth();

	const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
	const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
	const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

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
				if (tile.tilesetId == -1)
					continue;

				// Get the currect vertexlayer
				sf::VertexArray* vertexLayer = *(vertexLayers.end() - 1);
				// Get the current quad
				sf::Vertex* quad = &(*vertexLayer)[(i * width + j) * 4];

				// Calculate texture coordinates, based on the tilenumer
				unsigned int tileNumber = tile.id;
				int tu = tileNumber % (tileSet.getSize().x / tileWidth);
				int tv = tileNumber / (tileSet.getSize().x / tileWidth);

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

	//for each object layer
	for (auto objects : objLayers)
	{
		//int totalObjects = objLayers

		//for each object IN object layer
		for (auto object : objects->GetObjects())
		{

			spriteVector.push_back(new sf::Sprite);
			std::cout << spriteVector.size() << std::endl;

			/*if (tmxTileSet->GetFirstGid() == NULL)
			{
			currentTileSet = 1;
			}*/
			const int gid = object->GetGid();

			for (auto tileset : map.GetTilesets())
			{
				if (tileset->GetFirstGid() < gid)
				{
					tmxTileSet = tileset;
					break;
				}
			}
			int real_id = gid - tmxTileSet->GetFirstGid();


			unsigned int intId = real_id;
			objId.push_back(intId);
			if (real_id == -1)
				continue;

			//const Tmx::MapTile tile = objects->GetTile(j, i);
			//if (tile.tilesetId == -1)
			//	continue;

			real_id &= ~(FLIPPED_HORIZONTALLY_FLAG |
				FLIPPED_VERTICALLY_FLAG |
				FLIPPED_DIAGONALLY_FLAG);


			int tu2 = real_id % (tileSet.getSize().x / tileWidth);
			int tv2 = real_id / (tileSet.getSize().x / tileWidth);



			sf::IntRect textureSource; //= Objectets 4 rektangel värden

			textureSource.left = tu2 * tileWidth;
			textureSource.top = tv2 * tileHeight;

			textureSource.width = tileWidth;
			textureSource.height = tileHeight;

			sf::Vector2f topLeft(textureSource.left, textureSource.top); //left-top
			sf::Vector2f topRight((tu2 + 1) * textureSource.width, textureSource.top); //width-top
			sf::Vector2f botRight((tu2 + 1) * textureSource.width, (tv2 + 1) * textureSource.height); //width-height
			sf::Vector2f botLeft(textureSource.left, (tv2 + 1) * textureSource.height); //left-height

			sf::Texture* tempTex = new sf::Texture();
			sf::Image* tempImg = new sf::Image();
			tempImg->loadFromFile(tmxTileSet->GetImage()->GetSource());
			tempTex->loadFromImage(*tempImg, textureSource);

			//tempSprite->setTexture(tempTex);
			//tempSprite->setTextureRect(textureSource);
			spriteVector[spriteVector.size() - 1]->setPosition(object->GetX(), object->GetY());

			spriteVector[spriteVector.size() - 1]->setTexture(*tempTex);



			objs.push_back(object);
		}

	}

	// Create a window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tmx Example");
	sf::Event event;
	while (window.isOpen())
	{
		// Poll events for this window
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}
		//		std::cout << spriteVector[2]->getPosition << std::endl;
		/*for (size_t i = 0; i <= objId.size() - 1; i++)
		{
		std::cout << objId[i] << std::endl;
		}*/
		//for (int i = objId.size()-1; i > 0; i--) {
		//	std::cout << objId[i] << std::endl;
		//}

		window.clear();



		// Create a non-default renderstate, and bind our tileset texture to it
		sf::RenderStates states;
		states.texture = &tileSet;
		for (auto i : vertexLayers)
		{
			// Render a vertexarray, with the custom renderstate
			//window.draw(*i, states);
		}
		for (int i = 0; i < spriteVector.size() - 1; i++)
		{
			window.draw(*spriteVector[i]);
		}

		//sf::RenderStates objstates;
		//
		//for (auto i : sprObj)
		//{
		//	//objstates.texture = sprObj[i]->getFillColor();
		//	window.draw(*i, objstates);
		//}

		window.display();
	}
}