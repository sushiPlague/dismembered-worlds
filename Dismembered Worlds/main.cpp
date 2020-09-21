#include "Game.h"

Game* game = nullptr;

int main(int argc, char* args[])
{

    game = new Game();

    //Start up SDL and create window
    if (!game->init("Dismembered Worlds", 1280, 720))
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        game->handleEvents();
    }

    game->clean();

	return 0;
}