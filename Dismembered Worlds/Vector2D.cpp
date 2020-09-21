#include "Vector2D.h"

Vector2D::Vector2D()
	: x(0.0f), y(0.0f)
{}

Vector2D::Vector2D(float xPos, float yPos)
	: x(xPos), y(yPos)
{}

void Vector2D::print()
{
	printf("x: %f, y: %f\n", x, y);
}