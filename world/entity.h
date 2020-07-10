#ifndef ENTITY_H
#define ENTITY_H
#include "SDL2/SDL.h"
struct Entity{
	char height;
	unsigned int type;
	double x;
	double y;
	double velocity;
	double angle;	
	SDL_Texture* texture;
	SDL_Rect rect;
};
#endif
