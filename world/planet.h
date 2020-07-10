#ifndef PLANET_H
#define PLANET_H
#define PLANETSIZE 64
#include "point.h"
struct Planet{
	unsigned int radius;
	int center_x;
	int center_y;
	struct Point points[PLANETSIZE];
};
#endif
