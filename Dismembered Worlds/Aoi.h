#pragma once

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "EventHandler.h"
#include "Collider.h"
#include "CollisionHandler.h"
#include "Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f
#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Animation;

class Aoi : public Character
{
public:
	Aoi(Properties*  properties);

public:
	virtual void draw();
	virtual void update(float dt);
	virtual void clean();

private:
	void animationState();

private:
	Animation* animation;
	RigidBody* rigidBody;
	float jumpTime; // Time Aoi takes to move upward
	float attackTime; // Time given to animate Aoi's attack
	float jumpForce; // Force applied on Aoi so that he can move upward
	Collider* collider;
	Vector2D lastSafePosition; // Make sure whether ie. Aoi hit a wall and move him back to the last saved safe position
	
// States
private:
	bool isRunning;
	bool isJumping;
	bool isFalling;
	bool isGrounded;
	bool isAttacking;
	bool isHit;
	bool isDead;
};