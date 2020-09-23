#include "EventHandler.h"

EventHandler* EventHandler::instance = nullptr;

EventHandler::EventHandler()
{
	keyStates = SDL_GetKeyboardState(nullptr);
}

EventHandler* EventHandler::getInstance()
{
	return instance = (instance != nullptr) ? instance : new EventHandler();
}

void EventHandler::listen()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::getInstance()->quit();
			break;
		case SDL_KEYDOWN:
			keyDown();
			break;
		case SDL_KEYUP:
			keyUp();
			break;
		}
	}
}

bool EventHandler::isKeyDown(SDL_Scancode key)
{
	return keyStates[key] == 1 ? true : false;
}

void EventHandler::keyUp()
{
	keyStates = SDL_GetKeyboardState(nullptr);
}

void EventHandler::keyDown()
{
	keyStates = SDL_GetKeyboardState(nullptr);
}