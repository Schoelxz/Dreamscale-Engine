#pragma once
// Include tmx-stuff we use in the program
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObjectGroup.h>
#include <Tmx\TmxObject.h>
#include <Tmx\TmxTileset.h>
#include <Tmx\TmxTileLayer.h>
#include <Tmx\TmxImage.h>
#include <Tmx\TmxTile.h>
#include <Tmx\TmxMapTile.h>

// Include part of the standard library
#include <cassert>
#include <iostream>
#include <array>

// Include sfml to render our layers
#include <SFML\Graphics.hpp>

class TmxHandler
{
public:
	TmxHandler();
	~TmxHandler();
};

