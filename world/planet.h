#ifndef PLANET_H
#define PLANET_H
#define PLANETSIZE 7
#include "point.h"
struct Planet{
	unsigned int radius;
	struct Point points[PLANETSIZE];
};
#endif
