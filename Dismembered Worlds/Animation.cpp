#include "Animation.h"

Animation::Animation()
{}

void Animation::draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
	TextureManager::getInstance()->drawFrame(textureID, x, y, spriteWidth, spriteHeight, spriteRow, spriteFrame, flip);
}

void Animation::update()
{
	spriteFrame = (SDL_GetTicks() / animationSpeed) % frameCount;
}

void Animation::setProperties(std::string textureID, int spriteRow, int frameCount, int animationSpeed)
{
	this->textureID = textureID;
	this->spriteRow = spriteRow;
	this->frameCount = frameCount;
	this->animationSpeed = animationSpeed;
}