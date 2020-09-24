#pragma once

#include <iostream>
#include <string>
#include <stdio.h>

class Point
{
public:
	Point(float xPos = 0, float yPos = 0) : x(xPos), y(yPos) {}

public:
	inline Point operator+(const Point& point2) const
	{
		return Point(x + point2.x, y + point2.y);
	}

	inline friend Point operator+=(Point& point1, const Point& point2)
	{
		point1.x += point2.x;
		point1.y += point2.y;

		return point1;
	}

	inline Point operator-(const Point& point2) const
	{
		return Point(x - point2.x, y - point2.y);
	}

	inline friend Point operator-=(Point& point1, const Point& point2)
	{
		point1.x -= point2.x;
		point1.y -= point2.y;

		return point1;
	}

	inline Point operator*(const float scalar) const
	{
		return Point(x * scalar, y * scalar);
	}

	void print(std::string message = "No message.")
	{
		printf("Message: %s | x: %f, y: %f\n", message.c_str(), x, y);
	}

public:
	float x, y;
};
