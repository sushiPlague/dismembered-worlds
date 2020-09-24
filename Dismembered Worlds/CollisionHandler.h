#pragma once

#include <SDL.h>
#include <vector>

#include "TileLayer.h"
#include "Map.h"
#include "Game.h"

class CollisionHandler
{
public:
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	bool mapCollision(SDL_Rect a);
	static CollisionHandler* getInstance();

private:
	CollisionHandler();

private:
	static CollisionHandler* instance;
	TileMap collisionTileMap;
	TileLayer* collisionLayer;
};

