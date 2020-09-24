#include "CollisionHandler.h"
#include "Game.h"

CollisionHandler* CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler()
{
	collisionLayer = (TileLayer*)Game::getInstance()->getMap()->getMapLayers().back();
	collisionTileMap = collisionLayer->getTileMap();
}

CollisionHandler* CollisionHandler::getInstance()
{
	return instance = (instance != nullptr) ? instance : new CollisionHandler();
}

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b)
{
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::mapCollision(SDL_Rect a)
{
	int tileSize = 32;
	int rowCount = 25;
	int columnCount = 60;

	int left_tile = a.x / tileSize;
	int right_tile = (a.x + a.w) / tileSize;

	int top_tile = a.y / tileSize;
	int bottom_tile = (a.y + a.h) / tileSize;

	if (left_tile < 0)
	{
		left_tile = 0;
	}

	if (right_tile > columnCount)
	{
		right_tile = columnCount;
	}

	if (top_tile < 0)
	{
		top_tile = 0;
	}

	if (bottom_tile > rowCount)
	{
		bottom_tile = rowCount;
	}

	for (int i = left_tile; i <= right_tile; ++i)
	{
		for (int j = top_tile; j <= bottom_tile; ++j)
		{
			if (collisionTileMap[j][i] > 0)
			{
				return true;
			}
		}
	}

	return false;
}