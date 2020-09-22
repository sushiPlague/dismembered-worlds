#include "Game.h"

Game* Game::instance = nullptr;
Aoi* aoi = nullptr;

Game::Game()
{}

Game::~Game()
{}

bool Game::init(const char* title)
{
	bool isInitialized = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		isInitialized = false;
	}
	else
	{
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			isInitialized = false;
		}
		else
		{
			SDL_Surface* gameIcon = IMG_Load("assets/icons/dismembered-worlds-icon.png");
			SDL_SetWindowIcon(gWindow, gameIcon);

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				isInitialized = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					isInitialized = false;
				}
				else
				{
					TextureManager::getInstance()->loadTexture("aoi", "assets/sprite-sheets/aoi.png");
					aoi = new Aoi(new Properties("aoi", 100, 100, 64, 64));

					isRunning = true;
				}
			}
		}
	}

	return isInitialized;
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	aoi->draw();
	SDL_RenderPresent(gRenderer);
}

void Game::update(float dt)
{
	aoi->update(0);
}

void Game::clean()
{
	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Destroy textures
	TextureManager::getInstance()->clean();

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

Game* Game::getInstance()
{
	return instance = (instance != nullptr) ? instance : new Game();
}
