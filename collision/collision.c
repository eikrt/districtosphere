#include <stdlib.h>
#include <stdio.h>
#include "collision.h"
#include "../world/point.h"
int collides_line(SDL_Rect rect, struct Point* points) {

	int intersects = 0;

	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
	x1 = (float)rect.x;
	y1 = (float)rect.y;
	x2 = (float)rect.x + rect.w;
	y2 = (float)rect.y;
	x3 = (float)rect.x;
	x3 = (float)rect.y + (float)rect.h;
	x4 = (float) rect.x + (float)rect.w;
	x4 = (float)rect.y + (float)rect.h;
	float px, py, px_1, py_1;
	if (points[0].y > points[1].y)
	{
		px = points[1].x;
		py = points[1].y;
		px_1 = points[0].x;
		py_1 = points[0].y;
}
	int intersects0 = is_line_intersection(x1,y1,x2,y2,(float)px,(float)py,(float)px_1,(float)py_1);	
	int intersects1 = is_line_intersection(x2, y2, x3, y3, px, py, px_1, py_1);	
	int intersects2 = is_line_intersection(x3, y3, x4, y4, px, py, px_1, py_1);	
	int intersects3 = is_line_intersection(x4, y4, x3, y3, px, py, px_1, py_1);	
		
	if (intersects0 == 1 || intersects1 == 1 || intersects2 == 1 || intersects3 == 1){
		intersects = 1;
	}
	return intersects;
	
}
int collides_rect(SDL_Rect rect, SDL_Rect another_rect) {
	

}





static int is_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y)
	{
		float i_x, i_y;
		float dx = p1_x - p0_x;
		float dy = p1_y - p0_y;
		float m1 = dy / dx;
		float c1 = p0_y - m1 * p0_x;

		dx = p3_x - p2_x;
		dy = p3_y - p2_y;
		float m2 = dy/dx;
		float c2 = p2_y - m2 * p2_x;
		if (m1 - m2 == 0){

				return 0;
				
			}

		else{
			
			i_x = (c2-c1) / (m1 - m2);
			i_y = m1*i_x + c1;
		}
		if (point_in_rect(p0_x, p0_y, p1_x, p1_y,i_x,i_y) == 1 && point_in_rect(p2_x,p2_y,p3_x,p3_y,i_x,i_y) == 1)
		{
			
		return 1;
			}
		else{
		return 0;
			}
 
}
static int point_in_rect(float x1, float y1, float x2, float y2, float i_x, float i_y) {
	float l,r,t,b;
    if(x1 < x2) {

        l = x1;

        r = x2;

    }

    else{

        l = x2;

        r = x1;

    }

    if(y1 < y2){

        t = y1;

        b = y2;

    }
    else {
        t = y1;
        b = y2;
    }
    if( (i_x+0.01) >= l && (i_x-0.01) <= r && 
            (i_y+0.01) >= t && (i_y-0.01) <= b ){
        return 1;
    }
    else{
        return 0;
}
}
