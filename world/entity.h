#ifndef ENTITY_H
#define ENTITY_H
#include "SDL2/SDL.h"
struct Entity{
	char height;
	unsigned int type;
	float x;
	float y;
	float dx;
	float dy;
	float velocity;
	float angle; //direction entity is facing
	float look_angle; // direction entity is looking
	SDL_Texture* texture;
	SDL_Rect rect;
};
#endif
