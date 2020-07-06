
#ifndef FILE_H_
#define FILE_H_
#include "../world/point.h"
#include "../world/planet.h"
#include "../world/entity.h"
void saveUniverse(struct Planet* map, const char* fileName);
void saveEntities(struct Entity* entities, const char* fileName);


struct Planet* openUniverse(const char* fileName);
struct Entity* openEntities(const char* fileName);
#endif
