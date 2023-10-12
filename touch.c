#include"touch.h"

//��Ļ����¼�������������x��y����
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
			if (et.type == EV_ABS && et.code == ABS_X)//��ȡx������
			{
				*x = et.value * (1.0 * 800 / 1024);
			}
			if (et.type == EV_ABS && et.code == ABS_Y)//��ȡy������
			{
				*y = et.value * (1.0 * 480 / 600);
			}

			if (et.type == EV_KEY && et.code == BTN_TOUCH)//��ָ�뿪��Ļ
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
	//��ȡ����
	int x0 = -1, y0 = -1;//��ʼ����
	int x1, y1;//ʵʱ����
	while (1)
	{
		int r = read(fd, &et, sizeof(et));
		if (r == sizeof(et))
		{
			if (et.type == EV_ABS && et.code == ABS_X)//��ȡx������
			{
				//x0ֻ��ȡһ��
				if (x0 == -1)
				{
					x0 = et.value * (1.0 * 800 / 1024);
				}
				//x1ʵʱ��ȡ
				x1 = et.value * (1.0 * 800 / 1024);;
			}
			if (et.type == EV_ABS && et.code == ABS_Y)//��ȡy������
			{
				if (y1 == -1)
				{
					y0 = et.value * (1.0 * 480 / 600);
				}
				y1 = et.value * (1.0 * 480 / 600);

			}

			if (et.type == EV_KEY && et.code == BTN_TOUCH && et.value == 0)//��ָ�뿪��Ļ
			{
				break;
			}
		}
	}
	printf("start(%d , %d) , leave(%d , %d)\n", x0, y0, x1, y1);
	int way;
	if (abs((y1 - y0) / (x1 - x0)) >= 1)//���ϻ������»�
	{
		if (y1 > y0)//�»�
		{
			printf("DOWN\n");
			way = DOWN;
		}
		else //�ϻ�
		{
			printf("UP\n");
			way = UP;
		}
	}
	else //�󻮻��һ�
	{
		if (x1 > x0)//��
		{
			printf("LEFT\n");
			way = LEFT;
		}
		else //�һ�
		{
			printf("RIGHT\n");
			way = RIGHT;
		}
	}
	return way;
}



