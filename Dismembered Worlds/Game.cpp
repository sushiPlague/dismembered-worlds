#include "Game.h"

Game::Game()
{}

Game::~Game()
{}

bool Game::init(const char* title, int width, int height)
{
	isInitialized = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		isInitialized = false;
	}
	else
	{
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			isInitialized = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				isInitialized = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					isInitialized = false;
				}
				else
				{
					grass = TextureManager::loadTexture(gRenderer, "assets/textures/grass.png");

					// temporary
					entities.push_back(Entity(Vector2D(0, 0), grass));
					entities.push_back(Entity(Vector2D(32, 0), grass));
					entities.push_back(Entity(Vector2D(64, 0), grass));
					entities.push_back(Entity(Vector2D(0, 32), grass));
				}
			}
		}
	}

	return isInitialized;
}

void Game::handleEvents()
{
	bool isRunning = true;

	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		clear();
		
		for (Entity& entity : entities)
		{
			render(entity);
		}

		update();
	}
}

void Game::render(Entity& entity)
{
	SDL_Rect srcRect;
	srcRect.x = entity.getCurrentFrame().x;
	srcRect.y = entity.getCurrentFrame().y;
	srcRect.w = entity.getCurrentFrame().w;
	srcRect.h = entity.getCurrentFrame().h;

	SDL_Rect dstRect;
	dstRect.x = entity.getPos().x * 2;
	dstRect.y = entity.getPos().y * 2;
	dstRect.w = entity.getCurrentFrame().w * 2;
	dstRect.h = entity.getCurrentFrame().h * 2;

	SDL_RenderCopy(gRenderer, entity.getTexture(), &srcRect, &dstRect);
}

void Game::update()
{
	SDL_RenderPresent(gRenderer);
}

void Game::clear()
{
	SDL_RenderClear(gRenderer);
}

void Game::clean()
{
	// Destroy textures
	SDL_DestroyTexture(grass);
	grass = NULL;

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
