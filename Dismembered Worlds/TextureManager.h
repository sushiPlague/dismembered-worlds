#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class TextureManager
{
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath);
};

