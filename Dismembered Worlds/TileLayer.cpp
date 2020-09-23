#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int p_tileSize, int p_rowCount, int p_columnCount, TileMap p_tileMap, TilesetList p_tilesets)
	: tileSize(p_tileSize), rowCount(p_rowCount), columnCount(p_columnCount), tileMap(p_tileMap), tilesets(p_tilesets)
{
	// Load textures
	for (auto& tileset : tilesets)
	{
		TextureManager::getInstance()->loadTexture(tileset.tilesetName, "assets/map/" + tileset.source);
	}
}

void TileLayer::render()
{
	for (unsigned int i = 0; i < rowCount; i++)
	{
		for (unsigned int j = 0; j < columnCount; j++)
		{
			int tileID = tileMap[i][j];

			if (tileID == 0)
			{
				continue;
			}
			else
			{
				int tilesetIndex = 0;

				if (tilesets.size() > 1)
				{
					for (unsigned int k = 1; k < tilesets.size(); k++)
					{
						if (tileID > tilesets[k].firstID && tileID < tilesets[k].lastID)
						{
							tileID = tileID + tilesets[k].tileCount - tilesets[k].lastID;
							tilesetIndex = k;
							break;
						}
					}
				}

				Tileset tileset = tilesets[tilesetIndex];
				int tileRow = tileID / tileset.columnCount;
				int tileColumn = tileID - tileRow * tileset.columnCount - 1;

				if (tileID % tileset.columnCount == 0)
				{
					tileRow--;
					tileColumn = tileset.columnCount - 1;
				}

				TextureManager::getInstance()->drawTile(tileset.tilesetName, tileset.tileSize, j * tileset.tileSize, i * tileset.tileSize, tileRow, tileColumn);
			}
		}
	}
}

void TileLayer::update()
{

}
