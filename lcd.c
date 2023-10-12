#include"lcd.h"

int fd = -1;
u32* plcd;
//��ӳ�䣬lcd
int open_lcd()
{
	//��lcd
	fd = open("/dev/fb0", O_RDWR);
	if (fd == -1)
	{
		perror("openlcd fail!");
		close(fd);
		return -1;
	}
	//��ӳ��
	plcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == plcd)
	{
		perror("openplcd fail!");
		return -1;
	}
	return fd;
}
//���㺯��
int draw_point(int x, int y, int color)
{

	*(plcd + y * 800 + x) = color;
}

//��ʼ��lcd��ȫ��ˢ��
int init_lcd(int color)
{
	int i, j;
	open_lcd();
	//ȫ��ˢ��
	for (i = 0; i < 480; i++)
	{
		for (j = 0; j < 800; j++)
		{
			draw_point(j, i, color);
		}
	}
	return fd;
}

//�ر�lcd��,���ӳ��
void close_lcd()
{
	munmap(plcd, 800 * 480 * 4);
	close(fd);
}