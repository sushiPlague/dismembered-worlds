#pragma once

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

#include "tinyxml2.h"
#include "TileLayer.h"
#include "Map.h"

class MapParser
{
public:
	static MapParser* getInstance();
	bool loadMap();
	void clean();
	inline Map* getMap(std::string id) { return maps[id]; }

private:
	MapParser();

private:
	bool parse(std::string id, std::string source);
	Tileset parseTileset(tinyxml2::XMLElement* xmlTileset);
	TileLayer* parseTileLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int columnCount);

private:
	static MapParser* instance; // Ensures that there is only one instance of the MapParser class (singleton)
	std::map<std::string, Map*> maps;
};

