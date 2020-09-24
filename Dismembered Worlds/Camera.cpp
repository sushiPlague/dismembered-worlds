#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera* Camera::getInstance()
{
	return instance = (instance != nullptr) ? instance : new Camera();
}

void Camera::update(float dt)
{
	if (target != nullptr)
	{
		cameraView.x = target->x - SCREEN_WIDTH / 2;
		cameraView.y = target->y - SCREEN_HEIGHT / 2;

		if (cameraView.x < 0)
		{
			cameraView.x = 0;
		}

		if (cameraView.y < 0)
		{
			cameraView.y = 0;
		}

		if (cameraView.x > (2 * SCREEN_WIDTH - cameraView.w))
		{
			cameraView.x = (2 * SCREEN_WIDTH - cameraView.w);
		}

		if (cameraView.y > (SCREEN_HEIGHT - cameraView.h))
		{
			cameraView.y = (SCREEN_HEIGHT - cameraView.h);
		}

		currentPosition = Vector2D(cameraView.x, cameraView.y);
	}
}


