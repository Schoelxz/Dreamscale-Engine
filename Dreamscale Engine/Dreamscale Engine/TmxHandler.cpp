#include "TmxHandler.h"

using namespace dse;

TmxHandler::TmxHandler() :
	m_map_index(0)
{
	std::cout << "class:	TmxHandler:	Constructed!" << std::endl;
	const std::string folder_name = ".\\TmxFiles\\";
	m_all_file_names = GetFileNamesInDir(folder_name);
	std::cout << "Prints all file names in folder inside	" << folder_name << ":" << std::endl;
	for (int i = 0; i < m_all_file_names.size(); i++)
	{
		m_all_file_names[i] = folder_name + m_all_file_names[i];
		std::cout << m_all_file_names[i] << std::endl;
	}
}

void TmxHandler::LoadObjects(const Tmx::Map& map)
{
	for (int i = 0; i < m_drawable.size(); i++) { delete m_drawable[i]; }
	for (int i = 0; i < m_sprite_textures.size(); i++) { delete m_sprite_textures[i]; }
	for (int i = 0; i < m_sprite_vector.size(); i++) { delete m_sprite_vector[i]; }
	for (int i = 0; i < m_rectangle_vector.size(); i++) { delete m_rectangle_vector[i]; }
	for (int i = 0; i < m_circle_vector.size(); i++) { delete m_circle_vector[i]; }
	for (int i = 0; i < m_convex_vector.size(); i++) { delete m_convex_vector[i]; }

	m_drawable.clear();
	m_sprite_textures.clear();
	m_sprite_vector.clear();
	m_rectangle_vector.clear();
	m_circle_vector.clear();
	m_convex_vector.clear();

	//const std::vector<Tmx::Tileset*> tmxTileSet = map.GetTilesets();
	const std::vector<Tmx::ObjectGroup*>& OBJ_LAYERS = map.GetObjectGroups(); //number of object layers

	//for each object layer												
	for (auto objects : OBJ_LAYERS)
	{
		//for each object in the object layer
		for (auto object : objects->GetObjects())
		{
			DeterminePolygonType(*object, map);
		}
	}
}

void TmxHandler::RefreshObjects()
{
	for (int i = 0; i < m_drawable.size(); i++)
	{
		switch (m_drawable[i]->type)
		{
			case DrawableType::CIRCLE_SHAPE:
			{
				dse::CircleShape* circle = m_drawable[i]->GetCircleShape();

				if (circle->GetVisible() == true)
					circle->setFillColor(sf::Color(0, 255, 0, 64));
				else
					circle->setFillColor(sf::Color(0, 255, 0, 0));
			}
				break;
			case DrawableType::CONVEX_SHAPE:
			{
				dse::ConvexShape* convex = m_drawable[i]->GetConvexShape();
			}
				break;
			case DrawableType::RECTANGLE_SHAPE:
			{
				dse::RectangleShape* rectangle = m_drawable[i]->GetRectangleShape();
				if (rectangle->GetVisible() == true)
					rectangle->setFillColor(sf::Color(0, 255, 0, 64));
				else
					rectangle->setFillColor(sf::Color(0, 255, 0, 0));
			}
				break;
			case DrawableType::SPRITE:
			{
				dse::Sprite* sprite = m_drawable[i]->GetSprite();
				if (sprite->GetVisible() == true)
					sprite->setColor(sf::Color(255, 255, 255, 255));
				else
					sprite->setColor(sf::Color(255, 255, 255, 0));
			}
				break;
			case DrawableType::VERTEX_ARRAY:
			{
				dse::VertexArray* vertex = m_drawable[i]->GetVertexShape();
			}
				break;
		}
	}
}

void TmxHandler::ParseAllMaps()
{
	//Parse all Maps (.tmx files) and save each in a mapVector
	for (size_t i = 0; i < m_all_file_names.size(); i++)
	{
		m_tmx_map = new Tmx::Map();
		m_tmx_map->ParseFile(m_all_file_names[i]);
		map_vector.insert(std::make_pair(m_all_file_names[i], m_tmx_map));
	}
}

std::vector<std::string> TmxHandler::GetFileNamesInDir(std::string folder)
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
	for (int i = 0; i < m_vertex_layers.size(); i++)
	{
		delete m_vertex_layers[i];
	}
	for (int i = 0; i < m_tileset_textures.size(); i++)
	{
		delete m_tileset_textures[i];
	}
	m_vertex_layers.clear();
	m_tileset_textures.clear();

	const std::vector<Tmx::Tileset*>& TMX_TILESET_MAP = map->GetTilesets();	//Number of tileset
	const std::vector<Tmx::TileLayer*>& TILE_LAYER = map->GetTileLayers();	//Number of tilelayers

	FLIPPED flipped = NONE;

	//push tilesets
	for (size_t i = 0; i < TMX_TILESET_MAP.size(); i++)
	{
		//Load the texture specifying the tileset
		sf::Texture* tileset = new sf::Texture();
		m_tileset_textures.push_back(tileset);
		const std::string FOLDER_NAME = ".\\TmxFiles";
		std::cout << FOLDER_NAME << TMX_TILESET_MAP[i]->GetImage()->GetSource() << std::endl;
		if (!tileset->loadFromFile(FOLDER_NAME + TMX_TILESET_MAP[i]->GetImage()->GetSource()))
		{
			assert(!"Couldn't load file!");
		}
	}

	// Get size for map and tiles
	const sf::Vector2i MAP_SIZE(map->GetWidth(), map->GetHeight());			//MapSize
	const sf::Vector2i TILE_SIZE(map->GetTileWidth(), map->GetTileHeight());	//TileSize

	//for each layers..
	for (auto layer : map->GetLayers()) 
	{
		//for each tileset..
		for (int t = 0; t < m_tileset_textures.size(); t++)
		{
			// Create a new vertexarray, acting as a list of quads
			sf::VertexArray* vertex_array = new sf::VertexArray(sf::Quads, MAP_SIZE.y * MAP_SIZE.x * 4);
			m_vertex_layers.push_back(vertex_array); //push the vertexArray into an VertexArray-Vector (vertexLayers)
			// For each tile in this layer...
			for (size_t i = 0; i < MAP_SIZE.y; ++i)
			{
				for (size_t j = 0; j < MAP_SIZE.x; ++j)
				{
					// Get the tile, and check if it's part of a tileset
					if (layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_TILE) 
					{
						Tmx::TileLayer* temp_layer = static_cast<Tmx::TileLayer*>(layer);
						const Tmx::MapTile TILE = temp_layer->GetTile(j, i);
						if (TILE.tilesetId == -1 || TILE.tilesetId != t)
							continue;

						const int GID = TILE.gid;

						int real_id = GID - TMX_TILESET_MAP[t]->GetFirstGid();

						sf::Vertex* quad = &(*vertex_array)[(i * MAP_SIZE.x + j) * 4];

						// Calculate texture coordinates, based on the tilenumer
						unsigned int tile_number = TILE.id;
						int tu = tile_number % (m_tileset_textures[t]->getSize().x / TILE_SIZE.x);
						int tv = tile_number / (m_tileset_textures[t]->getSize().x / TILE_SIZE.x);
						sf::Vector2i texture_cooridnates(tu, tv);
						/*
						The form that we align the vertices in to build our quads
						0 --- 1
						|     |
						|     |
						3 --- 2
						*/
						SetTile(quad, TILE, i, j, TILE_SIZE, texture_cooridnates);
					}
				}
			}
		}
	}
}

void TmxHandler::SetTile(sf::Vertex* &quad, Tmx::MapTile tile, int i, int j,
	const sf::Vector2i tile_size, sf::Vector2i texture_coord)
{
		FLIPPED flipped;
		// Position the vertices, as specified above
		quad[0].position = sf::Vector2f(j * tile_size.x, i * tile_size.y);
		quad[1].position = sf::Vector2f((j + 1) * tile_size.x, i * tile_size.y);
		quad[2].position = sf::Vector2f((j + 1) * tile_size.x, (i + 1) * tile_size.y);
		quad[3].position = sf::Vector2f(j * tile_size.x, (i + 1) * tile_size.y);

		// The default order to specify texture coordinates by.
		std::array<size_t, 4> texture_order = { 0, 1, 2, 3 };
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
			texture_order = { 2, 3, 0, 1 };
			break;
		case HORIZONTAL:
			texture_order = { 1, 0, 3, 2 };
			break;
		case VERTICAL:
			texture_order = { 3, 2, 1, 0 };
			break;
		case NONE:
			texture_order = { 0, 1, 2, 3 };
			break;
		default:
			break;
		}

		// Position the texture coordinates. Coordinates is specified in pixels, not 0-1
		quad[texture_order[0]].texCoords = sf::Vector2f(texture_coord.x * tile_size.x, texture_coord.y * tile_size.y);
		quad[texture_order[1]].texCoords = sf::Vector2f((texture_coord.x + 1) * tile_size.x, texture_coord.y * tile_size.y);
		quad[texture_order[2]].texCoords = sf::Vector2f((texture_coord.x + 1) * tile_size.x, (texture_coord.y + 1) * tile_size.y);
		quad[texture_order[3]].texCoords = sf::Vector2f(texture_coord.x * tile_size.x, (texture_coord.y + 1) * tile_size.y);

		quad[0].color = sf::Color(255, 255, 255, 255);
		quad[1].color = sf::Color(255, 255, 255, 255);
		quad[2].color = sf::Color(255, 255, 255, 255);
		quad[3].color = sf::Color(255, 255, 255, 255);
}

void TmxHandler::DrawMap(sf::RenderWindow& window)
{
	// Create a non-default renderstate, and bind our tilesets texture to it
	sf::RenderStates state;
	for (int i = 0; i < m_vertex_layers.size(); i++) {
		state.texture = m_tileset_textures[i % m_tileset_textures.size()]; //Draw every tileSet for every vertexLayer
		window.draw(*m_vertex_layers[i], state);
	}
}

void TmxHandler::DrawObjects(sf::RenderWindow & window)
{
	for (int i = 0; i < m_drawable.size(); i++) {
		window.draw(*m_drawable[i]->drawable);
	}
}

void TmxHandler::ResetVector()
{
	for (int i = 0; i < m_drawable.size(); i++)
	{
		delete m_drawable[i];
	}
	
	m_drawables.erase(m_drawables.begin(), m_drawables.end());
	
	m_drawable.clear();
	m_drawables.clear();
	m_map_index = 0;
}

std::vector<DrawableType*> TmxHandler::GetDrawable() const
{
	return m_drawable;
}

void TmxHandler::DeterminePolygonType(Tmx::Object & obj, const Tmx::Map & tmx_map)
{
	//sets the settings for each object depending on the objects type(shape)
	switch (obj.GetPrimitiveType())
	{
	case Tmx::TMX_PT_ELLIPSE: //circle
		{
			//std::cout << "ellipse" << std::endl;
			m_circle_vector.push_back(new dse::CircleShape());
			m_circle_vector.back()->SetName(obj.GetProperties().GetStringProperty("script"));
			m_circle_vector.back()->SetType(obj.GetType());
			m_circle_vector.back()->setRadius(obj.GetEllipse()->GetRadiusX());
			m_circle_vector.back()->setPosition(obj.GetX(), obj.GetY());
			m_circle_vector.back()->setFillColor(sf::Color(255, 255, 0, 64));
			m_drawable.push_back(new DrawableType(DrawableType::CIRCLE_SHAPE, m_circle_vector[m_circle_vector.size() - 1]));
			m_drawables.insert(std::make_pair(m_map_index++, m_drawable.back()));
			break;
		}
	case Tmx::TMX_PT_POLYGON: //polygon
		{
			//std::cout << "polygon" << std::endl;
			m_convex_vector.push_back(new dse::ConvexShape());
			m_convex_vector.back()->SetName(obj.GetName());
			m_convex_vector.back()->SetType(obj.GetType());
			int num_points = obj.GetPolygon()->GetNumPoints();
			m_convex_vector.back()->setPointCount(num_points);
			for (int i = 0; i < num_points; i++)
			{
				const sf::Vector2f POINT_POS = sf::Vector2f(obj.GetX() + obj.GetPolygon()->GetPoint(i).x, obj.GetY() + obj.GetPolygon()->GetPoint(i).y);
				m_convex_vector.back()->setPoint(i, POINT_POS);
			}
			m_convex_vector.back()->setFillColor(sf::Color(0, 0, 255, 64));
			m_drawable.push_back(new DrawableType(DrawableType::CONVEX_SHAPE, m_convex_vector.back()));
			m_drawables.insert(std::make_pair(m_map_index++, m_drawable.back()));
		}
			break;
	case Tmx::TMX_PT_POLYLINE: //polyline
		{
			//std::cout << "polyline" << std::endl;
			sf::VertexArray* vertex = new sf::VertexArray(sf::LineStrip, obj.GetPolyline()->GetNumPoints());
			int num_points = obj.GetPolyline()->GetNumPoints();
			for (int i = 0; i < num_points; i++)
			{
				const sf::Vector2f POINT_POS = sf::Vector2f(obj.GetX() + obj.GetPolyline()->GetPoint(i).x, obj.GetY() + obj.GetPolyline()->GetPoint(i).y);
				(*vertex)[i].position = POINT_POS;
				(*vertex)[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
			}
			m_drawable.push_back(new DrawableType(DrawableType::VERTEX_ARRAY, vertex));
			m_drawables.insert(std::make_pair(m_map_index++, m_drawable.back()));
		}
			break;
	case Tmx::TMX_PT_NONE:
	{
		if (obj.GetGid() == 0) //rectangle
		{
			m_rectangle_vector.push_back(new dse::RectangleShape());
			m_rectangle_vector.back()->SetName(obj.GetName());
			m_rectangle_vector.back()->SetType(obj.GetType());
			m_rectangle_vector.back()->setSize(sf::Vector2f(obj.GetWidth(), obj.GetHeight()));
			m_rectangle_vector.back()->setPosition(obj.GetX(), obj.GetY());

			m_drawable.push_back(new DrawableType(DrawableType::RECTANGLE_SHAPE, m_rectangle_vector.back()));
			m_drawables.insert(std::make_pair(m_map_index++, m_drawable.back()));
		}
		else //tileObject
		{
			const std::vector<Tmx::Tileset*> tmxTileSet = tmx_map.GetTilesets();

			int temp_current_tileset;
			const int HEIGHT = tmx_map.GetHeight();
			const int WIDTH = tmx_map.GetWidth();
			const int TILE_HEIGHT = obj.GetHeight();
			const int TILE_WIDTH = obj.GetWidth();

			const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
			const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
			const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;
			//std::cout << "tile" << std::endl;
			m_sprite_vector.push_back(new dse::Sprite());
			m_sprite_vector.back()->SetName(obj.GetName());

			const int GID = obj.GetGid();
			if (GID == 0)
				break;

			for (int i = tmxTileSet.size() - 1; i >= 0; i--)
			{
				if (tmxTileSet[i]->GetFirstGid() > GID)
				{
					temp_current_tileset = i;
					continue;
				}
				temp_current_tileset = i;
				break;
			}

			int real_id = GID - tmxTileSet[temp_current_tileset]->GetFirstGid();

			real_id &= ~(FLIPPED_HORIZONTALLY_FLAG |
				FLIPPED_VERTICALLY_FLAG |
				FLIPPED_DIAGONALLY_FLAG);

			int tu2 = real_id % (m_tileset_textures[temp_current_tileset]->getSize().x / TILE_WIDTH);
			int tv2 = real_id / (m_tileset_textures[temp_current_tileset]->getSize().x / TILE_WIDTH);

			sf::IntRect texture_source; //= Objectets 4 rektangel värden
			texture_source.left = tu2 * TILE_WIDTH;
			texture_source.top = tv2 * TILE_HEIGHT;
			texture_source.width = TILE_WIDTH;
			texture_source.height = TILE_HEIGHT;

			sf::Image* temp_image = new sf::Image();
			m_sprite_textures.push_back(new sf::Texture());

			const std::string FOLDER_NAME = ".\\TmxFiles";

			temp_image->loadFromFile(FOLDER_NAME + tmxTileSet[temp_current_tileset]->GetImage()->GetSource());
			m_sprite_textures[m_sprite_textures.size() - 1]->loadFromImage(*temp_image, texture_source);

			m_sprite_vector.back()->setPosition(obj.GetX(), obj.GetY() - obj.GetHeight());
			m_sprite_vector.back()->setTexture(*m_sprite_textures.back());
			delete temp_image;

			m_sprite_vector.back()->SetName(obj.GetName());
			m_sprite_vector.back()->SetType(obj.GetType());

			m_drawable.push_back(new DrawableType(DrawableType::SPRITE, m_sprite_vector.back()));
			m_drawables.insert(std::make_pair(m_map_index++, m_drawable.back()));
		}
			break;
	}
	default:
		break;
	}
}
