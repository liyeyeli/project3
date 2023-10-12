#include"lcd.h"

int fd = -1;
u32* plcd;
//打开映射，lcd
int open_lcd()
{
	//打开lcd
	fd = open("/dev/fb0", O_RDWR);
	if (fd == -1)
	{
		perror("openlcd fail!");
		close(fd);
		return -1;
	}
	//打开映射
	plcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == plcd)
	{
		perror("openplcd fail!");
		return -1;
	}
	return fd;
}
//画点函数
int draw_point(int x, int y, int color)
{

	*(plcd + y * 800 + x) = color;
}

//初始化lcd，全屏刷白
int init_lcd(int color)
{
	int i, j;
	open_lcd();
	//全屏刷白
	for (i = 0; i < 480; i++)
	{
		for (j = 0; j < 800; j++)
		{
			draw_point(j, i, color);
		}
	}
	return fd;
}

//关闭lcd屏,解除映射
void close_lcd()
{
	munmap(plcd, 800 * 480 * 4);
	close(fd);
}