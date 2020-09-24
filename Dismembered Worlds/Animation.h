#pragma once

#include <string>
#include <SDL.h>

#include "TextureManager.h"

class Animation
{
public:
	Animation();

public:
	void draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void update();
	void setProperties(std::string textureID, int spriteRow, int frameCount, int animationSpeed);

private:
	int spriteRow;
	int spriteFrame;
	int animationSpeed;
	int frameCount;
	std::string textureID;
};

