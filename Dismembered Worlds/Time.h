#pragma once

#include <SDL.h>

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const float TARGET_DELTATIME = 1.5f;

class Time
{
public:
	static Time* getInstance();
	void tick();
	float getDeltaTime();

private:
	Time();

private:
	static Time* instance; // Ensures that there is only one instance of the Time class (singleton)
	float deltaTime;
	float finalTime;
};

