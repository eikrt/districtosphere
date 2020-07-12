#ifndef COLLISION_H_
#define COLLISION_H_
#include "SDL2/SDL.h";
#include "../world/point.h";
int collides_line(SDL_Rect rect, struct Point* points);
int collides_rect(SDL_Rect rect, SDL_Rect another_rect);
static int is_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y);
#endif
