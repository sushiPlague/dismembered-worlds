#include "Aoi.h"
#include "Camera.h"
#include "Game.h"

Aoi::Aoi(Properties* properties)
	: Character(properties)
{
	isRunning = false;
	isJumping = false;
	isFalling = false;
	isGrounded = false;
	isAttacking = false;
	isHit = false;
	isDead = false;

	jumpTime = JUMP_TIME;
	jumpForce = JUMP_FORCE;

	collider = new Collider();
	collider->setPadding(-140, -110, 70, 50);

	rigidBody = new RigidBody();
	rigidBody->setGravity(3.0f);

	animation = new Animation();
	animation->setProperties(textureID, 0, 8, 100);
}

void Aoi::draw()
{
	animation->draw(transform->getX(), transform->getY(), width, height, flip);

	/* 
	** Draw box around Aoi for collision debugging (comment out)
	*/
	/*Vector2D cam = Camera::getInstance()->getCurrentPosition();
	SDL_Rect box = collider->get();
	box.x -= cam.getX();
	box.y -= cam.getY();
	SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &box);*/
}

void Aoi::update(float dt)
{
	isRunning = false;
	rigidBody->unsetForce();

	/*
	** Running forward
	*/
	if (EventHandler::getInstance()->getAxisKey(HORIZONTAL) == FORWARD && !isAttacking)
	{
		rigidBody->applyForceX(FORWARD * RUN_FORCE);
		flip = SDL_FLIP_NONE;
		isRunning = true;
	}

	/*
	** Running backward
	*/
	if (EventHandler::getInstance()->getAxisKey(HORIZONTAL) == BACKWARD && !isAttacking)
	{
		rigidBody->applyForceX(BACKWARD * RUN_FORCE);
		flip = SDL_FLIP_HORIZONTAL;
		isRunning = true;
	}

	/*
	** Attacking
	*/
	if (EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		rigidBody->unsetForce();
		isAttacking = true;
	}

	/*
	** Jumping
	*/
	if (EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_W) && isGrounded)
	{
		isJumping = true;
		isGrounded = false;
		rigidBody->applyForceY(UPWARD * jumpForce);
	}

	if (EventHandler::getInstance()->isKeyDown(SDL_SCANCODE_W) && isJumping && jumpTime > 0)
	{
		jumpTime -= dt;
		rigidBody->applyForceY(UPWARD * jumpForce);
	}
	else
	{
		isJumping = false;
		jumpTime = JUMP_TIME;
	}

	/*
	** Falling
	*/
	if (rigidBody->getVelocity().getY() > 0 && !isGrounded)
	{
		isFalling = true;
	}
	else
	{
		isFalling = false;
	}

	/*
	** Attack timer
	*/
	if (isAttacking && attackTime > 0)
	{
		attackTime -= dt;
	}
	else
	{
		isAttacking = false;
		attackTime = ATTACK_TIME;
	}
	
	// X axis movement
	rigidBody->update(dt);
	lastSafePosition.setX(transform->getX());
	transform->setX(transform->getX() + rigidBody->getPosition().getX());
	collider->set(transform->getX(), transform->getY(), 96, 96);

	if (CollisionHandler::getInstance()->mapCollision(collider->get()))
	{
		transform->setX(lastSafePosition.getX());
	}

	// Y axis movement
	rigidBody->update(dt);
	lastSafePosition.setY(transform->getY());
	transform->setY(transform->getY() + rigidBody->getPosition().getY());
	collider->set(transform->getX(), transform->getY(), 96, 96);

	if (CollisionHandler::getInstance()->mapCollision(collider->get()))
	{
		isGrounded = true;
		transform->setY(lastSafePosition.getY());
	}
	else
	{
		isGrounded = false;
	}

	origin->x = transform->getX() + width / 2;
	origin->y = transform->getY() + height / 2;

	animationState();
	animation->update();
}

void Aoi::animationState()
{
	animation->setProperties("aoi_idle", 0, 8, 100);

	if (isRunning)
	{
		animation->setProperties("aoi_run", 0, 8, 100);
	}

	if (isJumping)
	{
		animation->setProperties("aoi_jump", 0, 2, 200);
	}

	if (isFalling)
	{
		animation->setProperties("aoi_fall", 0, 2, 350);
	}

	if (isAttacking)
	{
		animation->setProperties("aoi_attack", 0, 6, 80);
	}

	if (isHit)
	{
		animation->setProperties("aoi_hit", 0, 4, 150);
	}

	if (isDead)
	{
		animation->setProperties("aoi_dead", 0, 6, 200);
		Game::getInstance()->quit();
	}
}

void Aoi::clean()
{
	TextureManager::getInstance()->dropTexture(textureID);
}
