#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ASIZE 250000000
int res1[ASIZE] ={0,};
int res2[ASIZE] ={0,}; 
int sum[4] = {0,};
typedef struct timeval tv;

double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec -start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("runtime = %lf sec\n", end.tv_usec /1000000.0);

	return end.tv_usec / 1000000.0;
}

void *task1(void *x)
{
	int i =0;
	for(i =0;i<(ASIZE/4);i++)
	{
		sum[0] += res2[4*i];
	}
	pthread_exit((void *)sum[0]);
}

void *task2(void *x)
{
	int i=0;
	for(i = 0;i<(ASIZE/4);i++)
	{
		sum[1] += res2[4*i+1];
	}

	pthread_exit((void *)sum[1]);
}

void *task3(void *x)
{
	int i =0;
	for(i = 0;i<(ASIZE/4);i++)
	{

		sum[2] += res2[4*i+2];
	}

	pthread_exit((void *)sum[2]);
}

void *task4(void *x)
{
	int i =0;
	for(i = 0;i<(ASIZE/4);i++)
	{
		sum[3] += res2[4*i+3];
	}

	pthread_exit((void *)sum[3]);
}

int main(void)
{
	unsigned int i, cnt = 0;
	tv start, end;
	pthread_t thread[4];
	memset(res1,-1,sizeof(res1));
	memset(res2,-1,sizeof(res2));

	pthread_create(&thread[0], NULL, task1,NULL);
	pthread_create(&thread[1], NULL, task2,NULL);
	pthread_create(&thread[2], NULL, task3,NULL);
	pthread_create(&thread[4], NULL, task4,NULL);	

	gettimeofday(&start,NULL);
	
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[3],NULL);
	pthread_join(thread[4],NULL);
	
	res1[ASIZE-1] = sum[0]+sum[1]+sum[2]+sum[3];
	res1[ASIZE-1] -= res2[ASIZE-1];
	res1[ASIZE-1] += res1[0];
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
	}
*/
	return 0;
}
