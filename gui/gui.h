#ifndef APP_H
#define APP_H
#include "SDL2/SDL.h"

const double ROTATION_SPEED = 0.01;
const int LANDER_SPEED = 100;
void init();
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Renderer* renderer);
int quit(SDL_Window *window);
#endif
