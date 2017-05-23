#include "TmxHandler.h"

enum FLIPPED
{
	DIAGONAL,
	HORIZONTAL,
	VERTICAL,
	NONE,
};

TmxHandler::TmxHandler() :
	mapIndex(0)
{
	
}

void TmxHandler::UpdateObjects()
{
	for (int i = 0; i < m_drawable.size(); i++)
	{
		switch (drawable[i]->t)
		{
			case DrawableType::CIRCLE_SHAPE:
			{
				dse::CircleShape* circle = drawable[i]->GetCircleShape();
				// Do typical circle stuff ...
				//std::cout << m_drawable[i]->GetCircleShape()->GetType() << std::endl;
				//std::cout << circle->GetName();

				if (circle->GetVisible() == true)
					circle->setFillColor(sf::Color(0, 255, 0, 64));
				else
					circle->setFillColor(sf::Color(0, 255, 0, 0));
				
			}
				break;
			case DrawableType::CONVEX_SHAPE:
			{
				dse::ConvexShape* convex = drawable[i]->GetConvexShape();
				//std::cout << convex->GetName() << std::endl;
				// Do typical convex stuff ...
			}
				break;
			case DrawableType::RECTANGLE_SHAPE:
			{
				dse::RectangleShape* rectangle = drawable[i]->GetRectangleShape();
				if (rectangle->GetVisible() == true)
					rectangle->setFillColor(sf::Color(0, 255, 0, 64));
				else
					rectangle->setFillColor(sf::Color(0, 255, 0, 0));
				//std::cout << rectangle->GetName() << std::endl;
			}
				break;
			case DrawableType::SPRITE:
			{
				dse::Sprite* sprite = drawable[i]->GetSprite();
				if (sprite->GetVisible() == true)
					sprite->setColor(sf::Color(255, 255, 255, 255));
				else
					sprite->setColor(sf::Color(255, 255, 255, 0));
				//std::cout << sprite->GetName() << std::endl;
			}
				break;
			case DrawableType::VERTEX_ARRAY:
			{
				dse::VertexArray* vertex = drawable[i]->GetVertexShape();
				//std::cout << vertex->GetName();
			}
				break;
		}
	}
}

void TmxHandler::ParseAllMaps()
{
	//Parse all Maps (.tmx files) and save each in a mapVector
	for (size_t i = 0; i < allFileNames.size(); i++)
	{
		map2 = new Tmx::Map();
		map2->ParseFile(allFileNames[i]);
		mapVector.insert(std::make_pair(allFileNames[i], map2));
	}
}

std::vector<std::string> TmxHandler::get_all_files_names_within_folder(std::string folder)
{
	std::vector<std::string> names;
	std::string search_path = folder + "/*.tmx*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void TmxHandler::LoadMap(Tmx::Map* map)
{
	//TODO: sf::VertexArray läcker 2 gånger varje gång en ny map laddas in, pga. vi inte delete:ar 2 instanser.
	for (int i = 0; i < vertexLayers.size(); i++)
	{
		delete vertexLayers[i];
	}
	for (int i = 0; i < tileSetTexture.size(); i++)
	{
		delete tileSetTexture[i];
	}
	vertexLayers.clear();
	tileSetTexture.clear();

	const std::vector<Tmx::Tileset*>& tmxTileSetMap = map->GetTilesets();	//Number of tileset
	const std::vector<Tmx::TileLayer*>& tileLayers = map->GetTileLayers();	//Number of tilelayers

	FLIPPED flipped = NONE;

	//push tilesets
	for (size_t i = 0; i < tmxTileSetMap.size(); i++)
	{
		//Load the texture specifying the tileset
		sf::Texture* tileset = new sf::Texture();
		tileSetTexture.push_back(tileset);
		if (!tileset->loadFromFile(tmxTileSetMap[i]->GetImage()->GetSource()))
		{
			assert(!"Couldn't load file!");
		}
	}

	// Get size for map and tiles
	const sf::Vector2i mapSize(map->GetWidth(), map->GetHeight());			//MapSize
	const sf::Vector2i tileSize(map->GetTileWidth(), map->GetTileHeight());	//TileSize

	//for each layers..
	for (auto layer : map->GetLayers()) 
	{
		//for each tileset..
		for (int t = 0; t < tileSetTexture.size(); t++)
		{
			// Create a new vertexarray, acting as a list of quads
			sf::VertexArray* vertexArray = new sf::VertexArray(sf::Quads, mapSize.y * mapSize.x * 4);
			vertexLayers.push_back(vertexArray); //push the vertexArray into an VertexArray-Vector (vertexLayers)
			// For each tile in this layer...
			for (size_t i = 0; i < mapSize.y; ++i)
			{
				for (size_t j = 0; j < mapSize.x; ++j)
				{
					// Get the tile, and check if it's part of a tileset
					if (layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_TILE) 
					{
						Tmx::TileLayer* tLayer = static_cast<Tmx::TileLayer*>(layer);
						const Tmx::MapTile tile = tLayer->GetTile(j, i);
						if (tile.tilesetId == -1 || tile.tilesetId != t)
							continue;

						const int gid = tile.gid;

						int real_id = gid - tmxTileSetMap[t]->GetFirstGid();

						sf::Vertex* quad = &(*vertexArray)[(i * mapSize.x + j) * 4];

						// Calculate texture coordinates, based on the tilenumer
						unsigned int tileNumber = tile.id;
						int tu = tileNumber % (tileSetTexture[t]->getSize().x / tileSize.x);
						int tv = tileNumber / (tileSetTexture[t]->getSize().x / tileSize.x);
						sf::Vector2i textureCoordinates(tu, tv);
						/*
						The form that we align the vertices in to build our quads
						0 --- 1
						|     |
						|     |
						3 --- 2
						*/
						SetTile(quad, tile, i, j, tileSize, textureCoordinates);
					}
				}
			}
		}
	}
}

void TmxHandler::SetTile(sf::Vertex* &quad, Tmx::MapTile tile, int i, int j,
	const sf::Vector2i tileSize, sf::Vector2i textCoord)
{
		FLIPPED flipped;
		// Position the vertices, as specified above
		quad[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
		quad[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
		quad[2].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);
		quad[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);

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
		quad[texOrder[0]].texCoords = sf::Vector2f(textCoord.x * tileSize.x, textCoord.y * tileSize.y);
		quad[texOrder[1]].texCoords = sf::Vector2f((textCoord.x + 1) * tileSize.x, textCoord.y * tileSize.y);
		quad[texOrder[2]].texCoords = sf::Vector2f((textCoord.x + 1) * tileSize.x, (textCoord.y + 1) * tileSize.y);
		quad[texOrder[3]].texCoords = sf::Vector2f(textCoord.x * tileSize.x, (textCoord.y + 1) * tileSize.y);

		quad[0].color = sf::Color(255, 255, 255, 255);
		quad[1].color = sf::Color(255, 255, 255, 255);
		quad[2].color = sf::Color(255, 255, 255, 255);
		quad[3].color = sf::Color(255, 255, 255, 255);
}

void TmxHandler::DrawMap(sf::RenderWindow& window)
{
	// Create a non-default renderstate, and bind our tilesets texture to it
	sf::RenderStates state;
	for (int i = 0; i < vertexLayers.size(); i++) {
		state.texture = tileSetTexture[i % tileSetTexture.size()]; //Draw every tileSet for every vertexLayer
		window.draw(*vertexLayers[i], state);
	}
}

void TmxHandler::DrawObjects(sf::RenderWindow & window)
{
	for (int i = 0; i < drawable.size(); i++) {
		window.draw(*drawable[i]->d);
	}
}

void TmxHandler::ResetVector()
{
	for (int i = 0; i < drawable.size(); i++)
	{
		delete drawable[i];
	}
	
	m_drawable.erase(m_drawable.begin(), m_drawable.end());
	
	drawable.clear();
	m_drawable.clear();
	mapIndex = 0;
}

void TmxHandler::DeterminePolygonType(Tmx::Object & obj, const Tmx::Map & m)
{
	//sets the settings for each object depending on the objects type(shape)
	switch (obj.GetPrimitiveType())
	{
	case Tmx::TMX_PT_ELLIPSE: //circle
		{
			//std::cout << "ellipse" << std::endl;
			circleVector.push_back(new dse::CircleShape());
			circleVector.back()->SetName(obj.GetProperties().GetStringProperty("script"));
			circleVector.back()->SetType(obj.GetType());
			circleVector.back()->setRadius(obj.GetEllipse()->GetRadiusX());
			circleVector.back()->setPosition(obj.GetX(), obj.GetY());
			circleVector.back()->setFillColor(sf::Color(255, 255, 0, 64));
			drawable.push_back(new DrawableType(DrawableType::CIRCLE_SHAPE, circleVector[circleVector.size() - 1]));
			m_drawable.insert(std::make_pair(mapIndex++, drawable.back()));
			break;
		}
	case Tmx::TMX_PT_POLYGON: //polygon
		{
			//std::cout << "polygon" << std::endl;
			convexVector.push_back(new dse::ConvexShape());
			convexVector.back()->SetName(obj.GetName());
			convexVector.back()->SetType(obj.GetType());
			int numPoints = obj.GetPolygon()->GetNumPoints();
			convexVector.back()->setPointCount(numPoints);
			for (int i = 0; i < numPoints; i++)
			{
				const sf::Vector2f pointPos = sf::Vector2f(obj.GetX() + obj.GetPolygon()->GetPoint(i).x, obj.GetY() + obj.GetPolygon()->GetPoint(i).y);
				convexVector.back()->setPoint(i, pointPos);
			}
			convexVector.back()->setFillColor(sf::Color(0, 0, 255, 64));
			drawable.push_back(new DrawableType(DrawableType::CONVEX_SHAPE, convexVector.back()));
			m_drawable.insert(std::make_pair(mapIndex++, drawable.back()));
		}
			break;
	case Tmx::TMX_PT_POLYLINE: //polyline
		{
			//std::cout << "polyline" << std::endl;
			sf::VertexArray* vertex = new sf::VertexArray(sf::LineStrip, obj.GetPolyline()->GetNumPoints());
			int numPoints = obj.GetPolyline()->GetNumPoints();
			for (int i = 0; i < numPoints; i++)
			{
				const sf::Vector2f pointPos = sf::Vector2f(obj.GetX() + obj.GetPolyline()->GetPoint(i).x, obj.GetY() + obj.GetPolyline()->GetPoint(i).y);
				(*vertex)[i].position = pointPos;
				(*vertex)[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
			}
			drawable.push_back(new DrawableType(DrawableType::VERTEX_ARRAY, vertex));
			m_drawable.insert(std::make_pair(mapIndex++, drawable.back()));
		}
			break;
	case Tmx::TMX_PT_NONE:
	{
		if (obj.GetGid() == 0) //rectangle
		{
			//std::cout << "rect" << std::endl;
			rectangleVector.push_back(new dse::RectangleShape());
			rectangleVector.back()->SetName(obj.GetName());
			rectangleVector.back()->SetType(obj.GetType());
			rectangleVector.back()->setSize(sf::Vector2f(obj.GetWidth(), obj.GetHeight()));
			rectangleVector.back()->setPosition(obj.GetX(), obj.GetY());
			rectangleVector.back()->SetVisible(false);
			
			drawable.push_back(new DrawableType(DrawableType::RECTANGLE_SHAPE, rectangleVector.back()));
			m_drawable.insert(std::make_pair(mapIndex++, drawable.back()));
		}
		else //tileObject
		{
			const std::vector<Tmx::Tileset*> tmxTileSet = m.GetTilesets();

			int tempCurrentTileset;
			const int height = m.GetHeight();
			const int width = m.GetWidth();
			const int tileHeight = obj.GetHeight();
			const int tileWidth = obj.GetWidth();

			const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
			const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
			const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;
			//std::cout << "tile" << std::endl;
			spriteVector.push_back(new dse::Sprite());
			spriteVector.back()->SetName(obj.GetName());

			const int gid = obj.GetGid();
			if (gid == 0)
				break;

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

			real_id &= ~(FLIPPED_HORIZONTALLY_FLAG |
				FLIPPED_VERTICALLY_FLAG |
				FLIPPED_DIAGONALLY_FLAG);

			int tu2 = real_id % (tileSetTexture[tempCurrentTileset]->getSize().x / tileWidth);
			int tv2 = real_id / (tileSetTexture[tempCurrentTileset]->getSize().x / tileWidth);

			sf::IntRect textureSource; //= Objectets 4 rektangel värden
			textureSource.left = tu2 * tileWidth;
			textureSource.top = tv2 * tileHeight;
			textureSource.width = tileWidth;
			textureSource.height = tileHeight;

			//TODO: Memory leak. tempImg and tempTex needs to be deleted. but if tempTex is deleted, the objects wont have textures.
			//Potential solution: create a vector of sprites to be saved in header file?
			sf::Image* tempImg = new sf::Image();
			spriteTextures.push_back(new sf::Texture());

			tempImg->loadFromFile(tmxTileSet[tempCurrentTileset]->GetImage()->GetSource());
			spriteTextures.back()->loadFromImage(*tempImg, textureSource);

			spriteVector.back()->setPosition(obj.GetX(), obj.GetY() - obj.GetHeight());
			spriteVector.back()->setTexture(*spriteTextures.back());
			delete tempImg;

			spriteVector.back()->SetName(obj.GetName());
			spriteVector.back()->SetType(obj.GetType());
			//spriteVector[spriteVector.size() - 1]->SetVisible(false);

			drawable.push_back(new DrawableType(DrawableType::SPRITE, spriteVector.back()));
			m_drawable.insert(std::make_pair(mapIndex++, drawable.back()));
		}
			break;
	}
	default:
		break;
	}
}
