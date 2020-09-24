#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(std::string enemyType, Properties* properties)
	: type(enemyType), Character(properties)
{
	isRunning = false;
	isAttacking = false;
	isHit = false;
	isDead = false;

	rigidBody = new RigidBody();
	rigidBody->setGravity(3.5);

	collider = new Collider();
	collider->setPadding(-140, -110, 70, 50);

	animation = new Animation();
	animation->setProperties(textureID, 0, 8, 100);
}

void Enemy::draw()
{
	animation->draw(transform->getX(), transform->getY(), width, height, SDL_FLIP_HORIZONTAL);
}

void Enemy::update(float dt)
{
	isRunning = false;
	rigidBody->unsetForce();

	/*
	** X axis movement
	*/
	rigidBody->update(dt);
	lastSafePosition.setX(transform->getX());
	transform->setX(transform->getX() + rigidBody->getPosition().getX());
	collider->set(transform->getX(), transform->getY(), 96, 96);

	if (CollisionHandler::getInstance()->mapCollision(collider->get()))
	{
		transform->setX(lastSafePosition.getX());
	}

	/*
	** Y axis movement
	*/
	rigidBody->update(dt);
	lastSafePosition.setY(transform->getY());
	transform->setY(transform->getY() + rigidBody->getPosition().getY());
	collider->set(transform->getX(), transform->getY(), 96, 96);

	if (CollisionHandler::getInstance()->mapCollision(collider->get()))
	{
		transform->setY(lastSafePosition.getY());
	}

	animation->update();
}

void Enemy::animationState()
{
	animation->setProperties(type + "_idle", 0, 4, 100);

	if (isRunning)
	{
		animation->setProperties(type + "_run", 0, 8, 100);
	}

	if (isAttacking)
	{
		animation->setProperties(type + "_attack", 0, 8, 200);
	}

	if (isHit)
	{
		animation->setProperties(type + "_hit", 0, 4, 150);
	}

	if (isDead)
	{
		animation->setProperties(type + "_dead", 0, 6, 200);
		Game::getInstance()->quit();
	}
}

void Enemy::clean()
{
	TextureManager::getInstance()->dropTexture(textureID);
}