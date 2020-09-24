#pragma once

#include <SDL.h>

#include "Point.h"
#include "Vector2D.h"
#include "Game.h"

class Camera
{
public:
	static Camera* getInstance();
	inline SDL_Rect getCameraView() { return cameraView; }
	inline Vector2D getCurrentPosition() { return currentPosition; }
	inline void setTarget(Point* camTarget) { target = camTarget; }
	void update(float dt);

private:
	Camera() {cameraView = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }

private:
	static Camera* instance; // Ensures that there is only one instance of the Camera class (singleton)
	Point* target;
	Vector2D currentPosition;
	SDL_Rect cameraView;
};

