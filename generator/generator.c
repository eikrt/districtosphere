#include "generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../world/planet.h"
#include "../world/point.h"
#include "../world/entity.h"
#include "../file/file.h"


const int GEN_SEED = 128;

static int noiseFromTable(int* table, int x, int y) { //gets values from lookup table
	int n = table[(y + GEN_SEED) % 256];
	return table[(n+ x) % 256];
}

static float interpol(float x, float y, float s) //vector interpolation
{
	return x + s * (y-x);
}

static float smoothening(float x, float y, float s) // smooths
{
	return interpol(x, y, s * s * (3-2*s));
}

static float noise(int* table,  float x, float y) // gets noise
{
	int x2 = x;
	int y2 = y;
	float x3 = x - x2;
	float y3 = y - y2;
	int s = noiseFromTable(table,x2, y2);
	int t = noiseFromTable(table,x2+1, y2);
	int u = noiseFromTable(table,x2, y2+1);
	int v = noiseFromTable(table,x2+1, y2+1);
	float low = smoothening(s, t, x3);
	float high = smoothening(u, v, x3);
	return smoothening(low, high, y3);
}

static float perlin(float x, float y, float freq, int depth) // main noise function
{
	int tableSize = 256;	
	int table [tableSize];
	srandom(time(0));
	for (int i = 0; i < tableSize; i++) {
			
			table[i] = random()%tableSize;
		}
	float xa = x*freq;
	float ya = y*freq;
	float amplification = 2;
	float val = 0;
	float division = 0.0;

	for(int i=0; i<depth; i++)
	{
      		division += tableSize * amplification;
        	val += noise(table,xa, ya) * amplification;
       		amplification /= 2;
       		xa *= 2;
        	ya *= 2;
	}
	float value = val/division; 
	return value;
}

static struct Planet* createPlanets(int sealevel){
	static struct Planet planets[SIZE];
	
	const int planetary_width = 8;
	for (int i = 0; i <SIZE; i++){

		planets[i].radius = 256;
			
			int planet_x = i * planets[i].radius * 4;
			int planet_y = (i % planetary_width)* 512*0;

			planets[i].center_x = planet_x;
			planets[i].center_y = planet_y;
		
			double angle=0;
			for (int j = 0; j < PLANETSIZE; j++) {
				angle = ((M_PI*2)/PLANETSIZE)*j;
				int val = perlin(i*32,j*32,0.01,1)*100+sealevel;
				int roundVal = floor(val);
			//	planets[0].points[i].height=roundVal;
				planets[i].points[j].x = planet_x + sin(angle) * (planets[i].radius+val);
				planets[i].points[j].y = planet_y + cos(angle) * (planets[i].radius+val);
				//printf("%i", val);
		}
	}

	
	
	
	

	//add 	
	return planets;
}
static struct Entity* createEntities() {

	static struct Entity entities[1];
	
	time_t t;
	srand((unsigned) time(&t));
	for (int i = 0; i < 1; i++) {

					
			entities[i].type = 1;
			entities[i].x = 512- 16;
			entities[i].y = 288 - 16;

			entities[i].rect.x = entities[i].x;	
			entities[i].rect.y = entities[i].y;	
			entities[i].rect.w = 32;	
			entities[i].rect.h = 32;	
			entities[i].velocity = 0;
			entities[i].dx = 0;					 entities[i].angle = 0.0;			
			entities[i].dy = 0;

		}

	return entities;
}
int create_universe(){

	struct Planet* map = createPlanets(32);
	struct Entity* entities = createEntities();
		
	saveUniverse(map, "world/universe.dat"); // file module 
	saveEntities(entities, "world/entities.dat");
	return 0;
}
