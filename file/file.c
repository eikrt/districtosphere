#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../world/entity.h"
#include "../world/planet.h"
#include "../world/point.h"
#include "../generator/generator.h"




void saveUniverse(struct Planet* map, const char* fileName)
{
  FILE* fp = fopen(fileName,"wb");

	if (!fp) return;
	for (int i = 0; i < SIZE; i++){
  			fwrite( &map[i], sizeof(struct Planet), 1, fp);
	}
  fclose(fp);
}
void saveEntities(struct Entity* entities, const char* fileName) {

	FILE* fp = fopen(fileName,"wb");
	
	if (!fp) return;
	for (int i = 0; i < SIZE; i++) {
		
		fwrite(&entities[i], sizeof(struct Entity), 1, fp);
	}
	fclose(fp);

}
struct Planet* openWorld(const char * fileName)
{
	FILE* fp = fopen(fileName,"rb");
	if( !fp ) return 0;
	int n = 0;
	static struct Planet universe[SIZE];
	struct Planet planet;

	for (n=0; !feof(fp); ++n) {
		fread(&planet, sizeof(struct Planet), 1, fp);
		universe[n] = planet; 
	}
fclose(fp);
return universe;
}
struct Entity* openEntities(const char * fileName) {
	FILE* fp = fopen(fileName,"rb");
	if (!fp) return 0;
	int n = 0;
	static struct Entity entities[1];
	struct Entity entity;
	for (n=0; !feof(fp); ++n) {
		fread(&entity, sizeof(struct Entity), 1, fp);
		entities[n] = entity;
	}
	fclose(fp);
	return entities;
}
