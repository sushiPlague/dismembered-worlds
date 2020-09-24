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

int EventHandler::getAxisKey(Axis axis)
{
	switch (axis)
	{
	case HORIZONTAL:
		if (isKeyDown(SDL_SCANCODE_D) || isKeyDown(SDL_SCANCODE_RIGHT))
		{
			return 1;
		}

		if (isKeyDown(SDL_SCANCODE_A) || isKeyDown(SDL_SCANCODE_LEFT))
		{ 
			return -1;
		}

		break;

	case VERTICAL:
		if (isKeyDown(SDL_SCANCODE_W) || isKeyDown(SDL_SCANCODE_UP))
		{
			return 1;
		}

		if (isKeyDown(SDL_SCANCODE_S) || isKeyDown(SDL_SCANCODE_DOWN))
		{
			return -1;
		}

		break;

	default:
		return 0;
	}
}