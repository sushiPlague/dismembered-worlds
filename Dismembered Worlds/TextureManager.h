#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <map>

#include "Game.h"

class TextureManager
{
public:
	static TextureManager* getInstance();
	bool loadTexture(std::string id, std::string filePath);
	void dropTexture(std::string id); // Removes texture from the map
	void draw(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE); // Draws static images
	void drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE); // Draws frames
	void clean(); // Cleans memory

private:
	TextureManager() {}

private:
	static TextureManager* instance; // Ensures that there is only one instance of the TextureManager class (singleton)
	std::map<std::string, SDL_Texture*> textureMap;
};

