#include "gui.h"
#include "SDL2/SDL.h"
#include "../generator/generator.h"
#include <stdio.h>
#include "../world/point.h"
#include "../world/entity.h"
#include "../world/planet.h"
#include "../file/file.h"
#include "../io/imgload.h"
const int SCREEN_WIDTH = 512*2;
const int SCREEN_HEIGHT = 288*2;
struct Camera{
	int x;
	int y;
};

int main() {
	init();
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL couldn't initialize");	
	}
	else {
		window = SDL_CreateWindow( "World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);       		
		if( window == NULL ) {
            	printf( "Error: %s\n", SDL_GetError());
        	}
		screenSurface = SDL_GetWindowSurface(window);
		SDL_SetRenderDrawColor(renderer, 0xFF,0xFF, 0xFF, 0xFF);

	}
	loop(window, screenSurface, renderer);
	return 0;
}

void init(){
	
}
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Renderer* renderer){
	int running = 1;
	struct Camera camera;
	camera.x = 0;
	camera.y = 0;
	SDL_Event e;

	struct Tile* map;
	struct Entity* entities;
	map = openWorld("../generator/world/universe.dat");
	entities = openEntities("../generator/world/entities.dat");
	int rgb[] = {255,255,255};

	



	while(running==1) {
		
		while (SDL_PollEvent(&e) != 0)
			{

			if (e.type == SDL_QUIT){
				running = 0;
			}
else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            camera.y -= 16;
				break;
                            case SDLK_DOWN:
                            camera.y += 16;
                            break;
                            case SDLK_LEFT:
                            camera.x -= 16;
                            break;
                            case SDLK_RIGHT:
                            camera.x += 16;
                            break;
			}
		}
}
		SDL_RenderClear( renderer );
		int renderX = camera.x / 16;
		int renderY = camera.y / 16;
			
	
						
			
		}
		SDL_RenderPresent(renderer);		
	SDL_Delay(32);

	
quit(window);
}
int quit(SDL_Window *window){
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
