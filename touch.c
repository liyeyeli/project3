#include"touch.h"

//屏幕点击事件，并保存点击的x，y坐标
int get_coordinate(int* x, int* y)
{
	struct input_event et;
	int fd = open("/dev/input/event0", O_RDONLY);
	if (fd == -1)
	{
		perror("openevent0 fail!");
		return -1;
	}
	while (1)
	{
		int r = read(fd, &et, sizeof(et));
		if (r == sizeof(et))
		{
			if (et.type == EV_ABS && et.code == ABS_X)//获取x轴坐标
			{
				*x = et.value * (1.0 * 800 / 1024);
			}
			if (et.type == EV_ABS && et.code == ABS_Y)//获取y轴坐标
			{
				*y = et.value * (1.0 * 480 / 600);
			}

			if (et.type == EV_KEY && et.code == BTN_TOUCH)//手指离开屏幕
			{
				if (et.value == 0)
				{
					break;
				}

			}
		}
	}
	return 0;
}

int get_fingle_move()
{
	struct input_event et;
	int fd = open("/dev/input/event0", O_RDONLY);
	if (fd == -1)
	{
		perror("openevent0 fail!");
		return -1;
	}
	//获取坐标
	int x0 = -1, y0 = -1;//初始坐标
	int x1, y1;//实时坐标
	while (1)
	{
		int r = read(fd, &et, sizeof(et));
		if (r == sizeof(et))
		{
			if (et.type == EV_ABS && et.code == ABS_X)//获取x轴坐标
			{
				//x0只获取一次
				if (x0 == -1)
				{
					x0 = et.value * (1.0 * 800 / 1024);
				}
				//x1实时获取
				x1 = et.value * (1.0 * 800 / 1024);;
			}
			if (et.type == EV_ABS && et.code == ABS_Y)//获取y轴坐标
			{
				if (y1 == -1)
				{
					y0 = et.value * (1.0 * 480 / 600);
				}
				y1 = et.value * (1.0 * 480 / 600);

			}

			if (et.type == EV_KEY && et.code == BTN_TOUCH && et.value == 0)//手指离开屏幕
			{
				break;
			}
		}
	}
	printf("start(%d , %d) , leave(%d , %d)\n", x0, y0, x1, y1);
	int way;
	if (abs((y1 - y0) / (x1 - x0)) >= 1)//向上或者向下划
	{
		if (y1 > y0)//下划
		{
			printf("DOWN\n");
			way = DOWN;
		}
		else //上划
		{
			printf("UP\n");
			way = UP;
		}
	}
	else //左划或右划
	{
		if (x1 > x0)//左划
		{
			printf("LEFT\n");
			way = LEFT;
		}
		else //右划
		{
			printf("RIGHT\n");
			way = RIGHT;
		}
	}
	return way;
}



