#include "Map.h"

void Map::render()
{
	for (auto& layer : mapLayers)
	{
		layer->render();
	}
}

void Map::update()
{
	for (auto& layer : mapLayers)
	{
		layer->update();
	}
}

std::vector<Layer*> Map::getMapLayers()
{
	return mapLayers;
}