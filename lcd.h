#ifndef __LCD_H__
#define __LCD_H__

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/mman.h>
#include<errno.h>

typedef unsigned int u32;
extern u32* plcd;
extern int fd;
int open_lcd();
int init_lcd(int color);
int draw_point(int x, int y, int color);
void close_lcd();




#endif 

