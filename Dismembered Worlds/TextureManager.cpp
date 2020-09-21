#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(SDL_Renderer* renderer, const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
	{
		printf("Failed to load texture! SDL_Error: %s\n", SDL_GetError());
	}

	return texture;
}
