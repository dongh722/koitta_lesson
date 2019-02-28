#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	pid_t pid;
	pid = fork(); //자식 프로세스가 있으면 0보다 큰 값(child pid값)을 반환
				// 자식 프로세스가 없으면 0

	if(pid>0)
		printf("P: pid = %d, cpid = %d\n",getpid(),pid);
	else if(!pid)
		printf("C: pid = %d, cpid = %d\n",getpid(),pid);
	else
	{
		perror("fork()");
		exit(-1);
	}

	return 0;
}
