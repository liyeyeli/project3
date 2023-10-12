#include"touch.h"
#include<sys/wait.h>


int main()
{
	int x, y;
	pid_t pid;
	pid = fork();
	//子进程：播放视频
	if (pid == 0)
	{
		execl("/IOT/yeli/MPlayer/son", "son", NULL);
		sleep(1);
		exit(0);
	}
	//父进程通过管道操纵子进程
	else if (pid > 0)
	{
		/*int fd = open("/IOT/yeli/test.fifo", O_WRONLY );
		if (fd == -1)
		{
			perror("open error");
			return -1;
		}
		get_coordinate(&x, &y);
		char* command = "killall -9 mplayer";
		int w = write(fd, command, strlen(command) + 1);
		if (w == -1)
		{
			perror("write error");
			return -1;
		}
		close(fd);*/
		wait(NULL);
	}
	

	//system("mplayer -loop 3 ./1.mp4");
	//system(buf);
	return 0;
}