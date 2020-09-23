#pragma once

#include "Vector2D.h"

#define MASS 1.0f
#define GRAVITY 9.0f
#define FORWARD 1
#define BACKWARD -1

class RigidBody
{
public:
	RigidBody()
	{
		mass = MASS;
		gravity = GRAVITY;
	}

public:
	inline void setMass(float mass) { this->mass = mass; }
	inline void setGravity(float gravity) { this->gravity = gravity; }
	inline float getMass() { return mass; }
	inline Vector2D getPosition() { return position; }
	inline Vector2D getVelocity() { return velocity; }
	inline Vector2D getAcceleration() { return acceleration; }

	/*
	** Force
	*/
	inline void applyForce(Vector2D force) { this->force = force; }
	inline void applyForceX(float x) { force.setX(x); }
	inline void applyForceY(float y) { force.setY(y); }
	inline void unsetForce() { force = Vector2D(0, 0); }
	
	/*
	** Friction
	*/
	inline void applyFriction(Vector2D friction) { this->friction = friction; }
	inline void unsetFriction() { friction = Vector2D(0, 0); }

	void update(float dt)
	{
		acceleration.setX((force.getX() + friction.getX()) / mass);
		acceleration.setY(gravity + force.getY() / mass);
		velocity = acceleration * dt;
		position = velocity * dt;
	}

private:
	float mass;
	float gravity;
	Vector2D force; // x and y axis force
	Vector2D friction; // ie. when the player is walking on ice, there is less friction
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
};