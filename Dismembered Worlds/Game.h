#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "TextureManager.h"
#include "EventHandler.h"
#include "Transform.h"
#include "Aoi.h"
#include "Time.h"
#include "Map.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

class Game
{
public:
	~Game();

public:
	bool init(const char* title);
	void handleEvents();
	void render();
	void update();
	void clean(); // Destroys entities and quits subsystems
	void quit();
	static Game* getInstance();
	inline bool running() { return isRunning; }
	inline SDL_Renderer* getRenderer() { return gRenderer; }

private:
	Game();

private:
	static Game* instance; // Ensures that there is only one instance of the Game class (singleton)
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	bool isRunning = false;
	Map* map;
};

