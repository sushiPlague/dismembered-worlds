#pragma once

#include <string>
#include <stdio.h>

class Vector2D
{
public:
	Vector2D(float xPos = 0, float yPos = 0) : x(xPos), y(yPos) {}

public:
	float getX() { return x; }
	float getY() { return y; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void print(std::string message = "No message.")
	{
		printf("Vector2D Message: %s | x: %.2f, y:%.2f\n", message.c_str(), x, y);
	}

// Overloaded operators
public:
	inline Vector2D operator+(const Vector2D& vector2) const
	{
		return Vector2D(x + vector2.x, y + vector2.y);
	}

	inline Vector2D operator-(const Vector2D& vector2) const
	{
		return Vector2D(x - vector2.x, y - vector2.y);
	}

	inline Vector2D operator*(const float scalar) const
	{
		return Vector2D(x * scalar, y * scalar);
	}

private:
	float x, y;
};

