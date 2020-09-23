#include "Game.h"
#include "MapParser.h"

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
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			isInitialized = false;
		}
		else
		{
			SDL_Surface* gameIcon = IMG_Load("assets/icons/dismembered-worlds-icon.png");
			
			if (gameIcon == NULL)
			{
				printf("Game icon could not be loaded! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				SDL_SetWindowIcon(gWindow, gameIcon);
			}

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
					if (!MapParser::getInstance()->loadMap())
					{
						printf("Failed to load the map!\n");
					}

					map = MapParser::getInstance()->getMap("map0");

					TextureManager::getInstance()->loadTexture("aoi_idle", "assets/sprite-sheets/Aoi/Idle.png");
					TextureManager::getInstance()->loadTexture("aoi_run", "assets/sprite-sheets/Aoi/Run.png");

					aoi = new Aoi(new Properties("aoi_idle", 100, 100, 200, 200));

					isRunning = true;
				}
			}
		}
	}

	return isInitialized;
}

void Game::handleEvents()
{
	EventHandler::getInstance()->listen();
}

void Game::render()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	map->render();
	aoi->draw();
	SDL_RenderPresent(gRenderer);
}

void Game::update()
{	
	float dt = Time::getInstance()->getDeltaTime();
	map->update();
	aoi->update(dt);
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

void Game::quit()
{
	isRunning = false;
}

Game* Game::getInstance()
{
	return instance = (instance != nullptr) ? instance : new Game();
}
