#pragma once

#include "Character.h"
#include "Animation.h"

class Animation;

class Aoi : public Character
{
public:
	Aoi(Properties*  properties);

public:
	virtual void draw();
	virtual void update(float dt);
	virtual void clean();

public:
	Animation* animation;
};

