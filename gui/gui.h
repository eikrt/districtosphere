#ifndef GUI_H_
#define GUI_H_
#include "SDL2/SDL.h"

const double ROTATION_SPEED = 0.03;
const int LANDER_SPEED = 30000;
const int MENU_FONT_SIZE = 10;
const int SCREEN_WIDTH = 512*2;
const int SCREEN_HEIGHT = 288*2;
void init();
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Renderer* renderer);
int quit(SDL_Window *window);
#endif
