#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Vector2D.h"

class Entity
{
public:
	Entity(Vector2D position, SDL_Texture* texture);

public:
	Vector2D& getPos();
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();

private:
	Vector2D pos;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
};

