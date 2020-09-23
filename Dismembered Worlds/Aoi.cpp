#include "Aoi.h"

Aoi::Aoi(Properties* properties)
	: Character(properties)
{
	rigidBody = new RigidBody();

	animation = new Animation();
	animation->setProperties(textureID, 0, 8, 100, SDL_FLIP_NONE);
}

void Aoi::draw()
{
	animation->draw(transform->getX(), transform->getY(), width, height);
}

void Aoi::update(float dt)
{
	animation->setProperties("aoi_idle", 0, 8, 100, SDL_FLIP_NONE);
	rigidBody->unsetForce();

	if (EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_A))
	{
		rigidBody->applyForce(3 * BACKWARD);
		animation->setProperties("aoi_run", 0, 8, 100, SDL_FLIP_HORIZONTAL);
	}

	if (EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_D))
	{
		rigidBody->applyForce(3 * FORWARD);
		animation->setProperties("aoi_run", 0, 8, 100, SDL_FLIP_NONE);
	}

	rigidBody->update(dt);
	transform->translateX(rigidBody->getPosition().getX());
	//transform->translateY(rigidBody->getPosition().getY());

	animation->update();
}

void Aoi::clean()
{
	TextureManager::getInstance()->clean();
}
