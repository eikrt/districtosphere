#ifndef PLANET_H
#define PLANET_H
#define PLANETSIZE 64
#include "point.h"
struct Planet{
	float radius;
	float center_x;
	float center_y;
	struct Point points[PLANETSIZE];
};
#endif
