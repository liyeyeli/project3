#include"bmp.h"

//通过延时展示多张图片
int ShowBmp()
{
	int color = 0x00ffffff;
	init_lcd(color);
	DIR* dir = NULL;
	dir = opendir("/IOT/yeli/ELe_picture");
	if (dir == NULL)
	{
		perror("opendir fail!");
		return -1;
	}
	struct dirent* dirp = NULL;
	while (dirp = readdir(dir))
	{
		if (strcmp(dirp->d_name, "4.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);
		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "5.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);
		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "6.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);
		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "7.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);

		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "8.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);

		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "9.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);

		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "10.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);

		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "11.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);

		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "12.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);

		}
		usleep(50);
		init_lcd(color);
		if (strcmp(dirp->d_name, "13.bmp") == 0)
		{
			draw_pic(100, 15, dirp->d_name);
			break;
		}
	}
}

//画图函数
int draw_pic(int x, int y, char* pic_name)
{
	//bmp的每个基本组成都不超过4个字节
	unsigned char buf[4];
	int fd1 = open(pic_name, O_RDONLY);
	if (fd1 == -1)
	{
		perror("openfd1 fail!");
		close(fd1);
		return -1;
	}
	//判断是否为bmp文件
	lseek(fd1, 0, SEEK_SET);
	read(fd1, buf, 2);
	if (buf[0] != 0x42 || buf[1] != 0x4D)
	{
		printf("this picture is not bmp");
		return -1;
	}
	//读位宽 4字节
	int bmp_w = 0;
	lseek(fd1, 0x12, SEEK_SET);
	read(fd1, &bmp_w, 4);
	//读位高 4字节
	int bmp_h = 0;
	lseek(fd1, 0x16, SEEK_SET);
	read(fd1, &bmp_h, 4);
	//读色深 2字节
	int bmp_colordepth = 0;
	lseek(fd1, 0x1C, SEEK_SET);
	read(fd1, &bmp_colordepth, 2);
	printf("bmp:%ld %ld %ld", bmp_w, bmp_h, bmp_colordepth);
	//读像素组的内容，并通过画点函数画出
	lseek(fd1, 54, SEEK_SET);
	int i, j;
	//分情况讨论：
	// 如果色深为32
	//因为bmp像素点记录数据为蓝绿红所以需要进行位操作
	char bmp_R, bmp_B, bmp_A, bmp_G;
	for (i = bmp_h - 1; i >= 0; i--)
	{
		for (j = 0; j < bmp_w; j++)
		{
			int color = 0;
			if (bmp_colordepth == 32)
			{
				//读完后光标会自动移动到末尾位置
				//read(fd1, &color, bmp_colordepth / 8);
				read(fd1, &bmp_B, 1);
				read(fd1, &bmp_G, 1);
				read(fd1, &bmp_R, 1);
				read(fd1, &bmp_A, 1);
				color = bmp_A << 24 | bmp_R << 16 | bmp_G << 8 | bmp_B;
				draw_point(x + j, y + i, color);
			}
			else if (bmp_colordepth == 24)
			{
				read(fd1, &bmp_B, 1);
				read(fd1, &bmp_G, 1);
				read(fd1, &bmp_R, 1);
				read(fd1, &bmp_A, 1);
				bmp_A = 0;
				color = bmp_A << 24 | bmp_R << 16 | bmp_G << 8 | bmp_B;
				draw_point(x + j, y + i, color);
			}
		}
		lseek(fd1, (4 - bmp_colordepth / 8 * bmp_w % 4) % 4, SEEK_CUR);
	}
	close(fd1);
}