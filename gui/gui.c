#include "gui.h"
#include "SDL2/SDL.h"
#include "../generator/generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
	int delta = 0;
	struct Camera camera;
	camera.x = 0;
	camera.y = 0;
	SDL_Event e;

	struct Planet* planets;
	struct Entity* entities;
	planets = openUniverse("../generator/world/universe.dat");
	

	entities = openEntities("../generator/world/entities.dat");
	
	int rgb[] = {255,255,255};

	

	SDL_Texture* landerTex = loadTexture(screenSurface, renderer, "../res/lander.bmp", rgb);
	
	for (int i = 0; i < ENTITYNUMBER; i++) {

                        int rgb2[] = {200,55,255};      
                        entities[i].texture = colorTexture(landerTex, rgb2);      
        }


	while(running==1) {
		delta = 10;
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
				case SDLK_a:
					entities[0].angle+=ROTATION_SPEED;
					break;
				case SDLK_d:
					
					entities[0].angle-=ROTATION_SPEED;
					break;

				case SDLK_w:
					entities[0].velocity += LANDER_SPEED;
				
				entities[0].dx += (cos(entities[0].angle) * entities[0].velocity)/ (delta * 1000);
				entities[0].dy+= (sin(entities[0].angle) * entities[0].velocity) / (delta * 1000);

					break;
				
				case SDLK_s:
					
				entities[0].dx += (cos(entities[0].angle) * entities[0].velocity)/ (delta * 1000);
				entities[0].dy+= (sin(entities[0].angle) * entities[0].velocity) / (delta * 1000);

					entities[0].velocity -= LANDER_SPEED;
                            		break;
			}
		}
}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear( renderer );
		int renderX = camera.x / 16;
		int renderY = camera.y / 16;
			
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		for (int i = 0; i < SIZE; i++) {
				for (int j=0; j<PLANETSIZE; j++){
					if (j < PLANETSIZE-1)

						SDL_RenderDrawLine(renderer,planets[i].points[j].x - camera.x, planets[i].points[j].y - camera.y, planets[i].points[j+1].x - camera.x, planets[i].points[j+1].y - camera.y);	
						else if (j == PLANETSIZE-1)
						SDL_RenderDrawLine(renderer,planets[i].points[j].x - camera.x, planets[i].points[j].y - camera.y, planets[i].points[0].x - camera.x, planets[i].points[0].y - camera.y);	
						
				}
			}
		for (int i = 0; i < ENTITYNUMBER; i++) {

				//logic:



				entities[i].x += entities[i].dx / (delta * 1000);
				entities[i].y += entities[i].dy / (delta * 1000);
				// draw:
				SDL_Rect renderRect;
	                        entities[i].rect.x = entities[i].x;
        	                entities[i].rect.y = entities[i].y;
	
                	        renderRect.x = entities[i].rect.x - camera.x;
                       		renderRect.y = entities[i].rect.y - camera.y;

                        	renderRect.w = 32;
                       		renderRect.h = 32;
				
                    		SDL_RenderCopyEx( renderer, entities[i].texture, NULL, &renderRect,entities[i].angle * (180 / M_PI),NULL,SDL_FLIP_NONE);

			}	
						
			
		
		SDL_RenderPresent(renderer);		
	SDL_Delay(32);
 }
	
quit(window);
}
int quit(SDL_Window *window){
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
