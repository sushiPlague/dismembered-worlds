#pragma once

#include "Vector2D.h"

/*
** All objects rendered to the screen need to be able to transform
*/

class Transform
{
public:
	Transform(float xPos = 0, float yPos = 0) : x(xPos), y(yPos) {}

public:
	float getX() { return x; }
	float getY() { return y; }
	void print(std::string message = "No message.")
	{
		printf("Transform Message: %s | x: %.2f, y:%.2f\n", message.c_str(), x, y);
	}

private:
	inline void translateX(float x) { this->x += x; }
	inline void translateY(float y) { this->y += y; }
	inline void translate(Vector2D vector) 
	{
		x += vector.getX();
		y += vector.getY();
	}

private:
	float x, y;
};
