#pragma once

#include <string>

#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Animation.h"

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Enemy : public Character
{
public:
	Enemy(std::string enemyType, Properties* properties);

public:
	virtual void draw();
	virtual void update(float dt);
	virtual void clean();
	void animationState();

private:
	Collider* collider;
	Animation* animation;
	RigidBody* rigidBody;
	Vector2D lastSafePosition;
	std::string type;
	//float attackTime; // Time given to animate Enemy's attack

// States
private:
	bool isRunning;
	bool isAttacking;
	bool isHit;
	bool isDead;
};

