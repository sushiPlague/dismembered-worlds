#pragma once

#include <string>
#include <vector>

#include "Layer.h"
#include "tinyxml2.h"

struct Tileset
{
	int firstID, lastID;
	int rowCount, columnCount;
	int tileCount, tileSize;
	std::string tilesetName, source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer
{
public:
	TileLayer(int p_tileSize, int p_rowCount, int p_columnCount, TileMap p_tileMap, TilesetList p_tilesets);

public:
	virtual void render();
	virtual void update();
	inline TileMap getTileMap() { return tileMap; }

private:
	int tileSize;
	int rowCount, columnCount;
	TileMap tileMap;
	TilesetList tilesets;
};

