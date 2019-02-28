#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	int i;
	pid_t pid;
	pid = fork(); //자식 프로세스가 있으면 0보다 큰 값
				// 자식 프로세스가 없으면 0

	if(pid>0)
	{
		for(;;)
		{
			for(i=0;i<33;i++) //context switching에 의해서 i값 보장
				printf("P");

			printf("\n");
		}
		
	}
	else if(!pid)
	{
		for(;;)
		{
			for(i=0;i<77;i++)
				printf("C");
			printf("\n");
		}
	}
	else
	{
		perror("fork()");
		exit(-1);
	}

	return 0;
}
