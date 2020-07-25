#ifndef FILE_H_
#define FILE_H_
#include "../world/point.h"
#include "../world/planet.h"
#include "../world/entity.h"
#include "../world/worlddata.h"
void saveUniverse(struct Planet* map, unsigned int planets_size, const char* fileName);
void saveEntities(struct Entity* entities, unsigned int planets_size, const char* fileName);
void saveData(struct WorldData data, const char* fileName);
struct Planet* openUniverse(const char* fileName);
struct Entity* openEntities(const char* fileName);
struct WorldData openWorldData(const char* fileName);
#endif
