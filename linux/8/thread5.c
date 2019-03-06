#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ASIZE 250000000
int res1[ASIZE] ={0,};
int res2[ASIZE] ={0,}; 
typedef struct timeval tv;

double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec -start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("runtime = %lf sec\n", end.tv_usec /1000000.0);

	return end.tv_usec / 1000000.0;
}

void func(void)
{
	int i;
	int sum = 0;
	res1[ASIZE-1] =0;
	for(i = 0; i < ASIZE-1;i++)
	{
		 res1[ASIZE-1] += res2[i];
	}
	res1[ASIZE-1] += res1[0];
}

int main(void)
{
	unsigned int i, cnt = 0;
	tv start, end;
	memset(res1,-1,sizeof(res1));
	memset(res2,-1,sizeof(res2));
	
	gettimeofday(&start,NULL);
	
	func();

	gettimeofday(&end, NULL);
	get_runtime(start,end);

	printf("%d\n",-res1[ASIZE-1]);
/*
	for(cnt=0; cnt< ASIZE;cnt++)
	{
		printf("%d\t",-res1[cnt]);
		if(!((cnt+1)%8))
			printf("\n");
	}

	printf("\n");
	for(cnt=0; cnt< ASIZE;cnt++)
	{
		printf("%d\t",-res2[cnt]);
		if(!((cnt+1)%8))
			printf("\n");
	}*/

	return 0;
}
