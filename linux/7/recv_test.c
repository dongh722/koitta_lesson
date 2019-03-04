#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

int fd;
extern char *dev0;
jmp_buf env;

void call_exit(int signo)
{
	close_dev(fd);
	longjmp(env,1);
}

int main(void)
{
	int ret;
	char buf[32] = "0\r\n";
	int len = strlen(buf);
	fd = serial_config(dev0);
	signal(SIGINT, call_exit);

	if(!(ret = setjmp(env)))
		for(;;)
		{
			send_data(fd,buf,len,50);
			recv_data(fd);
		}
	return 0;
}
