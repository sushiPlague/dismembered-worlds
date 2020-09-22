#pragma once

#include <SDL.h>

#include "Transform.h"
#include "ObjectInterface.h"

/*
** Properties define how an object will be initialized
*/
struct Properties
{
public:
	Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
		: pTextureID(textureID), pX(x), pY(y), pWidth(width), pHeight(height), pFlip(flip)
	{}

public:
	std::string pTextureID;
	int pWidth, pHeight;
	float pX, pY;
	SDL_RendererFlip pFlip;
};

class GameObject : public ObjectInterface
{
public:
	GameObject(Properties* properties) 
		: textureID(properties->pTextureID), width(properties->pWidth), height(properties->pHeight), flip(properties->pFlip)
	{
		transform = new Transform(properties->pX, properties->pY);
	}

public:
	virtual void draw()=0;
	virtual void update(float dt)=0;
	virtual void clean()=0;

protected:
	Transform* transform;
	std::string textureID;
	int width, height;
	SDL_RendererFlip flip;
};

