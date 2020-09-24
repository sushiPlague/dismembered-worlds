#pragma once

#include <SDL.h>

#include "Game.h"

enum Axis
{
	HORIZONTAL, VERTICAL
};

class EventHandler
{
public:
	static EventHandler* getInstance();
	void listen();
	bool isKeyDown(SDL_Scancode key);
	int getAxisKey(Axis axis);

private:
	EventHandler();

private:
	void keyUp();
	void keyDown();

private:
	static EventHandler* instance; // Ensures that there is only one instance of the EventHandler class (singleton)
	const Uint8* keyStates;
};

