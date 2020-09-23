#include "MapParser.h"

MapParser* MapParser::instance = nullptr;

MapParser::MapParser()
{}

MapParser* MapParser::getInstance()
{
	return instance = (instance != nullptr) ? instance : new MapParser();
}

bool MapParser::loadMap()
{
	return parse("map0", "assets/map/dismembered-worlds-map_0.tmx");
}

void MapParser::clean()
{
	std::map<std::string, Map*>::iterator iter;

	for (iter = maps.begin(); iter != maps.end(); iter++)
	{
		iter->second = nullptr;
	}

	maps.clear();
}

bool MapParser::parse(std::string id, std::string source)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(source.c_str());

	if (doc.Error())
	{
		printf("Failed to load: %s\n", source.c_str());
		return false;
	}

	tinyxml2::XMLElement* root = doc.RootElement();

	int rowCount, columnCount, tileSize = 0;
	root->QueryIntAttribute("width", &columnCount);
	root->QueryIntAttribute("height", &rowCount);
	root->QueryIntAttribute("tilewidth", &tileSize);


	/*
	** Parsing tilesets
	*/
	TilesetList tilesets;

	for (tinyxml2::XMLElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
	{
		if (element->Value() == std::string("tileset"))
		{
			tilesets.push_back(parseTileset(element));
		}
	}

	/*
	** Parsing layers
	*/
	Map* map = new Map();

	for (tinyxml2::XMLElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
	{
		if (element->Value() == std::string("layer"))
		{
			TileLayer* tileLayer = parseTileLayer(element, tilesets, tileSize, rowCount, columnCount);
			map->mapLayers.push_back(tileLayer);
		}
	}

	maps[id] = map;

	return true;
}

Tileset MapParser::parseTileset(tinyxml2::XMLElement* xmlTileset)
{
	Tileset tileset;

	tileset.tilesetName = xmlTileset->Attribute("name");
	xmlTileset->QueryIntAttribute("firstgid", &tileset.firstID);

	xmlTileset->QueryIntAttribute("tilecount", &tileset.tileCount);
	tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

	xmlTileset->QueryIntAttribute("columns", &tileset.columnCount);
	tileset.rowCount = tileset.tileCount / tileset.columnCount;
	
	xmlTileset->QueryIntAttribute("tilewidth", &tileset.tileSize);

	tinyxml2::XMLElement* image = xmlTileset->FirstChildElement();
	tileset.source = image->Attribute("source");
	
	return tileset;
}

TileLayer* MapParser::parseTileLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int columnCount)
{
	tinyxml2::XMLElement* data = nullptr;

	for (tinyxml2::XMLElement* element = xmlLayer->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
	{
		if (element->Value() == std::string("data"))
		{
			data = element;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tileMap(rowCount, std::vector<int>(columnCount, 0));

	for (int row = 0; row < rowCount; row++)
	{
		for (int column = 0; column < columnCount; column++)
		{
			std::getline(iss, id, ',');
			std::stringstream converter(id);
			converter >> tileMap[row][column];

			if (!iss.good())
			{
				break;
			}
		}
	}

	return (new TileLayer(tileSize, rowCount, columnCount, tileMap, tilesets));
}