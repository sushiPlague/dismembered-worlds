#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>

#include "TextureManager.h"
#include "Entity.h"

class Game
{
public:
	Game();
	~Game();

public:
	bool init(const char* title, int width, int height);
	void handleEvents();
	void render(Entity& entity);
	void update();
	void clear(); // Clears the screen before rendering
	void clean(); // Destroys entities and quits subsystems

private:
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	bool isInitialized = false;
	std::vector<Entity> entities;

// Textures
private:
	SDL_Texture* grass = NULL;
};

