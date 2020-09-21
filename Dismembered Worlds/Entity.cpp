#include "Entity.h"

Entity::Entity(Vector2D position, SDL_Texture* tex)
	: pos(position), texture(tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

Vector2D& Entity::getPos()
{
	return pos;
}

SDL_Texture* Entity::getTexture()
{
	return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
