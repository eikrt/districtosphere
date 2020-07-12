#ifndef COLLISION_H_
#define COLLISION_H_
#include "SDL2/SDL.h";
#include "../world/point.h";
int collide_line(SDL_Rect* rect, struct Point* points);
int collide_rect(SDL_Rect* rect, SDL_Rect* another_rect);
#endif
