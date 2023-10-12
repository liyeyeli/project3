#ifndef __TOUCH_H__
#define __TOUCH_H__


#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
#include"bmp.h"
#include<linux/input.h>

int get_coordinate(int* x, int* y);
int get_fingle_move();




#endif 


