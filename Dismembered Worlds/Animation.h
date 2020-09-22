#pragma once

#include <string>
#include <SDL.h>

#include "TextureManager.h"

class Animation
{
public:
	Animation();

public:
	void draw(float x, float y, int spriteWidth, int spriteHeight);
	void update();
	void setProperties(std::string textureID, int spriteRow, int frameCount, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int spriteRow;
	int spriteFrame;
	int animationSpeed;
	int frameCount;
	std::string textureID;
	SDL_RendererFlip flip;
};

