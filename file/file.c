#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../world/entity.h"
#include "../world/planet.h"
#include "../world/point.h"
#include "../world/worlddata.h"
#include "../generator/generator.h"

struct WorldData openWorldData(const char* fileName) {
	FILE* fp = fopen(fileName,"rb");
	if (!fp) return;
	int n = 0;
	static struct WorldData world_data;
	for (n=0; !feof(fp); ++n) {
			fread(&world_data, sizeof(struct WorldData), 1, fp);
		}
	fclose(fp);
	return world_data;
}
void saveUniverse(struct Planet* map, unsigned int planets_size, const char* fileName)
{

  FILE* fp = fopen(fileName,"wb");
	if (!fp) return;
	for (int i = 0; i < planets_size; i++){
  			fwrite( &map[i], sizeof(struct Planet), 1, fp);
	}

  fclose(fp);
}
void saveEntities(struct Entity* entities, unsigned int entity_number, const char* fileName) {

	FILE* fp = fopen(fileName,"wb");
	
	if (!fp) return;
	for (int i = 0; i < entity_number; i++) {
		
		fwrite(&entities[i], sizeof(struct Entity), 1, fp);
	}
	
	fclose(fp);

}
void saveData(struct WorldData world_data, const char* fileName) {
	FILE* fp = fopen(fileName,"wb");
	if (!fp) return;
	fwrite(&world_data, sizeof(struct WorldData), 1, fp);
	fclose(fp);
} 
struct Planet* openUniverse(const char * fileName)
{
	FILE* fp = fopen(fileName,"rb");
	if( !fp ) return;
	int n = 0;
	struct Planet universe[1];
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

