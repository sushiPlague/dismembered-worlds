#include "Game.h"
#include "Time.h"

int main(int argc, char* args[])
{
    //Start up SDL and create window
    if (!Game::getInstance()->init("Dismembered Worlds"))
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        while (Game::getInstance()->running())
        {
            Game::getInstance()->handleEvents();
            Game::getInstance()->update();
            Game::getInstance()->render();
            Time::getInstance()->tick();
        }
    }

    Game::getInstance()->clean();

	return 0;
}