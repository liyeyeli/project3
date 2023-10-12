#include"bmp.h"

//ͨ����ʱչʾ����ͼƬ
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

//��ͼ����
int draw_pic(int x, int y, char* pic_name)
{
	//bmp��ÿ��������ɶ�������4���ֽ�
	unsigned char buf[4];
	int fd1 = open(pic_name, O_RDONLY);
	if (fd1 == -1)
	{
		perror("openfd1 fail!");
		close(fd1);
		return -1;
	}
	//�ж��Ƿ�Ϊbmp�ļ�
	lseek(fd1, 0, SEEK_SET);
	read(fd1, buf, 2);
	if (buf[0] != 0x42 || buf[1] != 0x4D)
	{
		printf("this picture is not bmp");
		return -1;
	}
	//��λ�� 4�ֽ�
	int bmp_w = 0;
	lseek(fd1, 0x12, SEEK_SET);
	read(fd1, &bmp_w, 4);
	//��λ�� 4�ֽ�
	int bmp_h = 0;
	lseek(fd1, 0x16, SEEK_SET);
	read(fd1, &bmp_h, 4);
	//��ɫ�� 2�ֽ�
	int bmp_colordepth = 0;
	lseek(fd1, 0x1C, SEEK_SET);
	read(fd1, &bmp_colordepth, 2);
	printf("bmp:%ld %ld %ld", bmp_w, bmp_h, bmp_colordepth);
	//������������ݣ���ͨ�����㺯������
	lseek(fd1, 54, SEEK_SET);
	int i, j;
	//��������ۣ�
	// ���ɫ��Ϊ32
	//��Ϊbmp���ص��¼����Ϊ���̺�������Ҫ����λ����
	char bmp_R, bmp_B, bmp_A, bmp_G;
	for (i = bmp_h - 1; i >= 0; i--)
	{
		for (j = 0; j < bmp_w; j++)
		{
			int color = 0;
			if (bmp_colordepth == 32)
			{
				//���������Զ��ƶ���ĩβλ��
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