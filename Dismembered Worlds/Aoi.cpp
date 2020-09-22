#include "Aoi.h"

Aoi::Aoi(Properties* properties)
	: Character(properties)
{
	animation = new Animation();
	animation->setProperties(textureID, 2, 6, 100, SDL_FLIP_NONE);
}

void Aoi::draw()
{
	animation->draw(transform->getX(), transform->getY(), width, height);
}

void Aoi::update(float dt)
{
	animation->update();
}

void Aoi::clean()
{
	TextureManager::getInstance()->clean();
}
