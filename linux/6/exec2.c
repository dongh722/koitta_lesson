#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int status;
	pid_t pid;

	if((pid = vfork())>0) //vfork -> child만 생성하고 메모리는 복사 하지 않음
	{
		wait(&status);
		printf("ls -al test Sucess\n");
	}
	else if(!(pid))
	{
		execlp("ls","ls","-a","-l",0);
	}

	return 0;
}
