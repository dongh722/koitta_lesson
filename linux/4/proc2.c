#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	pid_t pid;
	pid = fork(); //자식 프로세스가 있으면 0보다 큰 값
				// 자식 프로세스가 없으면 0

	if(pid>0)
		printf("P\n");
	else if(!pid)
		printf("C\n");
	else
	{
		perror("fork()");
		exit(-1);
	}

	return 0;
}
