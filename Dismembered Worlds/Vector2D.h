#pragma once

#include <stdio.h>

class Vector2D
{
public:
	Vector2D();
	Vector2D(float xPos, float yPos);
	
public:
	void print();

public:
	float x, y;
};

