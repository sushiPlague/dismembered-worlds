#pragma once

class ObjectInterface
{
public:
	virtual void draw() = 0;
	virtual void update(float dt) = 0;
	virtual void clean() = 0;
};
