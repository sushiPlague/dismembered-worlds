#include "Time.h"

Time* Time::instance = nullptr;

Time::Time()
{}

Time* Time::getInstance()
{
	return instance = (instance != nullptr) ? instance : new Time();
}

void Time::tick()
{
	deltaTime = (SDL_GetTicks() - finalTime) * SCREEN_TICKS_PER_FRAME;

	if (deltaTime > TARGET_DELTATIME)
	{
		deltaTime = TARGET_DELTATIME;
	}

	finalTime = SDL_GetTicks();
}

float Time::getDeltaTime()
{
	return deltaTime;
}