#pragma once

#include <string>

#include "GameObject.h"

class Character : public GameObject
{
public:
	Character(Properties* properties)
		: GameObject(properties)
	{}

public:
	virtual void draw() = 0;
	virtual void update(float dt) = 0;
	virtual void clean() = 0;

protected:
	std::string name;
};

