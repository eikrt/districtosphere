#include <stdlib.h>
#include <stdio.h>
#include "collision.h"
#include "../world/point.h"
int collides_line(SDL_Rect rect, struct Point* points) {

	int intersects = 0;

	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
	x1 = rect.x;
	y1 = rect.y;
	x2 = rect.x + rect.w;
	y2 = rect.y;
	x3 = rect.x;
	x3 = rect.y + rect.h;
	x4 = rect.x + rect.w;
	x4 = rect.y + rect.h;
	int intersects0 = is_line_intersection(x1, y1, x2, y2, points[0].x, points[0].y, points[1].x, points[1].y);	
	int intersects1 = is_line_intersection(x2, y2, x3, y3, points[0].x, points[0].y, points[1].x, points[1].y);	
	int intersects2 = is_line_intersection(x3, y3, x4, y4, points[0].x, points[0].y, points[1].x, points[1].y);	
	int intersects3 = is_line_intersection(x4, y4, x3, y3, points[0].x, points[0].y, points[1].x, points[1].y);	
	if (intersects0 == 1 || intersects1 == 1 || intersects2 == 1 || intersects3 == 1)
		intersects = 1;
	return intersects;
}
int collides_rect(SDL_Rect rect, SDL_Rect another_rect) {
	

}
void asdf() {

}




static int is_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y)
	{
    float s1_x, s1_y, s2_x, s2_y, sn, tn, sd, td, t;
	float i_x, i_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;
 
    sn = -s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y);
    sd = -s2_x * s1_y + s1_x * s2_y;
    tn =  s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x);
    td = -s2_x * s1_y + s1_x * s2_y;
 
    if (sn >= 0 && sn <= sd && tn >= 0 && tn <= td)
    {
        t = tn / td;
            i_x = p0_x + (tn * s1_x);
            i_y = p0_y + (tn * s1_y);
        return 1;
    }
 
    return 0;
}
