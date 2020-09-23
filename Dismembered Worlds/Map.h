#pragma once

#include <vector>

#include "Layer.h"
#include "Vector2D.h"

class Map
{
public:
	void render();
	void update();
	std::vector<Layer*> getMapLayers();

private:
	friend class MapParser;
	std::vector<Layer*> mapLayers;
};

