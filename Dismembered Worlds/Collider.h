#pragma once

#include <SDL.h>

using Box = SDL_Rect;

class Collider
{
public:
	inline Box get() { return box; }
	inline void setPadding(int x, int y, int w, int h) { padding = { x, y, w, h }; }
	void set(int x, int y, int w, int h)
	{
		box =
		{
			x - padding.x,
			y - padding.y,
			w - padding.w,
			h - padding.h
		};
	}

private:
	Box box;
	Box padding; // Space between an entity and it's collision rectangle (box)
};
