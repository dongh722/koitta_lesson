#include <time.h>
#include <stdio.h>
#include<stdlib.h>

#define SYSCALL_NUM 256
void *sys_call_table[SYSCALL_NUM] = {0,};
int random;

int my_open(char *str)
{
	printf("my_open() System call\n");
	printf("str = %s\n",str);
}

int test_open(char *str,int meta1, int meta)
{

}

int my_read(int fd, char *buf, int size)
{
	printf("my_read() System call\n");
	printf("fd = %d, buf = %s, size = %d\n",fd,buf,size);
}

int my_write(int fd, char *buf, int size)
{
	printf("my_write() System call\n");
	printf("fd = %d, buf = %s, size = %d\n",fd,buf,size);
}

void my_close(int fd)
{
	printf("my_close() System call\n");
	printf("fd = %d\n",fd);
}

void kill_proc(int signum)
{
	printf("signum = %\n",signum);
}

void (*my_signal(int signum, void(*handler)(int)))(int)
{
	printf("my_signal() System Call\n");
	printf("signum = %d\n",signum);
	handler(signum);
}

void init_sys_call_table(void)
{

	srand(time(NULL));

	random - rand() %2 +1;
	if (randnum%2) sys_call_table[0] = my_open;
	if
	sys_call_table[1] = my_read;
	sys_call_table[2] = my_write;
	sys_call_table[3] = my_close;
	sys_call_table[4] = my_signal;
}

// 반환 형 
//int 인자 타입 
void syscall(int syscall_num)
{
	char filename[32] = "text.txt"
	switch(syscall_num)
	{
		case 0://int (*)(char*)
			if(random %2)
				((int (*)(char*)) sys_call_table[0])(filename);
			else
				((int (*)(char*,int,int)) sys_call_table[0])(filename);

			break;
		case 1:// int (*)(int,char *, int)
			((int(*)(int,char *,int))sys_call_table[1])(fd,buf,len);
			break;
		case 2:// int (*)(int,char *, int)
			((int(*)(int,char *,int))sys_call_table[2])(fd,buf,len);
			break;
		case 3:// void (*)(int)
			((void (*)(int))sys_call_table[3])(fd);
			break;
		case 4://void (*)(int) (*)
			//(void(*)(int) (*)(int,void (*)			
			break;
	}
}

int main(void)
{
	int i;
	init_sys_call_table();

	for(i = 0; i<5; i++)
		syscall(i);
	return 0;
}
