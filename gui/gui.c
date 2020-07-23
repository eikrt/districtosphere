#include "gui.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "../generator/generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../world/point.h"
#include "../world/entity.h"
#include "../world/planet.h"
#include "../file/file.h"
#include "../io/imgload.h"
#include "../utilities/camera.h"
#include "../collision/collision.h"
const SDL_Texture* lander_texture;
int inited = 0;
int main() {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL couldn't initialize");	
	}
	else {
		window = SDL_CreateWindow( "Districtosphere", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

void init(struct Planet** planets, struct Entity** entities){
	
		
	*planets = openUniverse("../generator/world/universe.dat");
	*entities = openEntities("../generator/world/entities.dat");
	struct Entity* d_entities;
	d_entities = *entities;
	for (int i = 0; i < ENTITYNUMBER; i++) {

                        int rgb2[] = {200,55,255};      
                      d_entities[i].texture = colorTexture(lander_texture, rgb2);      
        }
	inited = 1;
}

void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Renderer* renderer){
	int menu_on = 1;
	int running = 1;
	int selected_menu_button = 0;
	int delta = 0;
	struct Camera camera;
	camera.x = 0;
	camera.y = 0;
	SDL_Event e;
	struct Planet* planets;
	struct Entity* entities;
	//load world
	
	int rgb[] = {255,255,255};
	//load textures
	lander_texture = loadTexture(screenSurface, renderer, "../res/lander.bmp", rgb);
	

	//init(&planets,&entities);

	

	TTF_Init();

	TTF_Font* sans = TTF_OpenFont("../res/fonts/8bitoperator.ttf", MENU_FONT_SIZE);
	if (sans == NULL) {
			printf("font not found");
		}

	SDL_Color white = {255,255,255};
	SDL_Color yellow = {10,255,125};

	SDL_Surface* msg_surface = TTF_RenderText_Solid(sans, "Crew", white);
	SDL_Surface* continue_surface = TTF_RenderText_Solid(sans, "Continue", white);
	SDL_Surface* create_surface = TTF_RenderText_Solid(sans, "New", white);


	SDL_Surface* load_surface = TTF_RenderText_Solid(sans, "Load", white);
	SDL_Surface* options_surface = TTF_RenderText_Solid(sans, "Options", white);
	SDL_Surface* exit_surface = TTF_RenderText_Solid(sans, "Exit", white);
	
	
	SDL_Surface* msg_surface_selected = TTF_RenderText_Solid(sans, "Crew", yellow);
	SDL_Surface* continue_surface_selected = TTF_RenderText_Solid(sans, "Continue", yellow);
	SDL_Surface* create_surface_selected = TTF_RenderText_Solid(sans, "New", yellow);


	SDL_Surface* load_surface_selected = TTF_RenderText_Solid(sans, "Load", yellow);
	SDL_Surface* options_surface_selected = TTF_RenderText_Solid(sans, "Options", yellow);
	SDL_Surface* exit_surface_selected = TTF_RenderText_Solid(sans, "Exit", yellow);
//	msg_surface = TTF_RenderText_Solid(sans, "Speed: "+ entities[0]);
	SDL_Rect msg_rect;
	SDL_Rect continue_rect;
	SDL_Rect create_rect;
	SDL_Rect load_rect;
	SDL_Rect options_rect;
	SDL_Rect exit_rect;

	msg_rect.x=16;
	msg_rect.y=SCREEN_HEIGHT-60;
	msg_rect.w=64;
	msg_rect.h=16;

	continue_rect.x = 16;
	continue_rect.y = 16;
	continue_rect.w = MENU_FONT_SIZE * 8;
	continue_rect.h = 16;
	
	create_rect.x = 16;
	create_rect.y = 30;
	create_rect.w = MENU_FONT_SIZE * 3;
	create_rect.h = 16;

	load_rect.x = 16;
	load_rect.y = 44;
	load_rect.w = MENU_FONT_SIZE * 5;
	load_rect.h = 16;
	
	options_rect.x = 16;
	options_rect.y = 58;
	options_rect.w = MENU_FONT_SIZE * 7;
	options_rect.h = 16;

	exit_rect.x = 16;
	exit_rect.y = 72;
	exit_rect.w = MENU_FONT_SIZE * 4;
	exit_rect.h = 16;




	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(renderer,msg_surface);
	SDL_Texture* continue_texture = SDL_CreateTextureFromSurface(renderer,continue_surface);
	SDL_Texture* create_texture = SDL_CreateTextureFromSurface(renderer,create_surface);
	SDL_Texture* load_texture = SDL_CreateTextureFromSurface(renderer,load_surface);
	SDL_Texture* options_texture = SDL_CreateTextureFromSurface(renderer,options_surface);
	SDL_Texture* exit_texture = SDL_CreateTextureFromSurface(renderer,exit_surface);

	SDL_Texture* msg_texture_selected = SDL_CreateTextureFromSurface(renderer,msg_surface_selected);
	SDL_Texture* continue_texture_selected = SDL_CreateTextureFromSurface(renderer,continue_surface_selected);
	SDL_Texture* create_texture_selected = SDL_CreateTextureFromSurface(renderer,create_surface_selected);
	SDL_Texture* load_texture_selected = SDL_CreateTextureFromSurface(renderer,load_surface_selected);
	SDL_Texture* options_texture_selected = SDL_CreateTextureFromSurface(renderer,options_surface_selected);
	SDL_Texture* exit_texture_selected = SDL_CreateTextureFromSurface(renderer,exit_surface_selected);


	SDL_FreeSurface(msg_surface);
	SDL_FreeSurface(continue_surface);
	SDL_FreeSurface(create_surface);
	SDL_FreeSurface(load_surface);
	SDL_FreeSurface(options_surface);
	SDL_FreeSurface(exit_surface);
	
	SDL_FreeSurface(msg_surface_selected);
	SDL_FreeSurface(continue_surface_selected);
	SDL_FreeSurface(create_surface_selected);
	SDL_FreeSurface(load_surface_selected);
	SDL_FreeSurface(options_surface_selected);
	SDL_FreeSurface(exit_surface_selected);
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
				case SDLK_ESCAPE:
					menu_on = 1;
					break;
				case SDLK_RETURN:
					if (selected_menu_button == 0){
						menu_on = 0;
						if (!inited)
						init(&planets,&entities);
					}
					
			else if (selected_menu_button == 1){
						menu_on = 0;
						create_universe();
						init(&planets,&entities);
						
					}
					else if (selected_menu_button == 2){
						init(&planets,&entities);
						menu_on = 0;
					}
			else if (selected_menu_button == 3){
						menu_on = 0;
						return 0;
					}
			else if (selected_menu_button == 4){
						menu_on = 0;
						return 0;
					}
					break;
                       		case SDLK_UP:

					if (menu_on == 1 && selected_menu_button > 0)
						selected_menu_button--;
                        	    	camera.y -= 16;
				break;
                         	case SDLK_DOWN:
						
					if (menu_on == 1 && selected_menu_button < 4)
						selected_menu_button++;
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
		if (menu_on == 0) {
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
		
				//player movement

					entities[0].x += entities[0].dx / (delta * 1000);
					entities[0].y += entities[0].dy / (delta * 1000);
				// player actions
				//player collision
					for (int i = 0; i < SIZE; i++) {			
						for (int j = 0; j < PLANETSIZE-2; j++) {
							static struct Point points[2];
							points[0] = planets[i].points[j];
							points[1] = planets[i].points[j+1];
							if (collides_line(entities[0].rect, points) == 1) {
						return 0;				
						}
					} 
				}

				// draw:
			for (int i = 0; i < ENTITYNUMBER; i++) {
	
					//logic:
				
					// draw:
					SDL_Rect renderRect;
	                       		entities[i].rect.x = entities[i].x;
	        	                entities[i].rect.y = entities[i].y;
	
        	        	        renderRect.x = entities[i].rect.x - camera.x;
                	       		renderRect.y = entities[i].rect.y - camera.y;

                        		renderRect.w = 32;
                       			renderRect.h = 32;

                   	 		SDL_RenderCopyEx( renderer, entities[i].texture, NULL, &renderRect,entities[i].angle * (180 / M_PI),NULL,SDL_FLIP_NONE);
				

		//		SDL_RenderCopy(renderer, msg_texture, NULL, &msg_rect);
					}
}
else{
					if (selected_menu_button == 0)
						SDL_RenderCopy(renderer, continue_texture_selected, NULL, &continue_rect);

					else
						SDL_RenderCopy(renderer, continue_texture, NULL, &continue_rect);

					
					if (selected_menu_button == 1)
					SDL_RenderCopy(renderer, create_texture_selected, NULL, &create_rect);

					else
						SDL_RenderCopy(renderer, create_texture, NULL, &create_rect);
					
					if (selected_menu_button == 2)
					SDL_RenderCopy(renderer, load_texture_selected, NULL, &load_rect);

					else
						SDL_RenderCopy(renderer, load_texture, NULL, &load_rect);

					if (selected_menu_button == 3)
					SDL_RenderCopy(renderer, options_texture_selected, NULL, &options_rect);
					
					else
						SDL_RenderCopy(renderer, options_texture, NULL, &options_rect);
					
					if (selected_menu_button == 4)
					SDL_RenderCopy(renderer, exit_texture_selected, NULL, &exit_rect);
					
					else
						SDL_RenderCopy(renderer, exit_texture, NULL, &exit_rect);
}					
						
			
		SDL_RenderPresent(renderer);		
	SDL_Delay(16);
 }
//exit the program

SDL_DestroyTexture(msg_texture);	
SDL_DestroyTexture(continue_texture);	
SDL_DestroyTexture(create_texture);	
SDL_DestroyTexture(load_texture);	
SDL_DestroyTexture(options_texture);	
SDL_DestroyTexture(exit_texture);	
quit(window);
}
int quit(SDL_Window *window){
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
