#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//thread 실행 보장 필요

void *t1(void *x)
{
	int cnt;
	int *tmp;
	tmp = x;

	printf("arg x =%d\n",x);

	for(cnt = 1; cnt < *tmp; cnt++)
		printf("work from t1: %d * 2 = %d\n", cnt, cnt*2);

	printf("t1 finished\n");
}

void *t2(void *x)
{
	int cnt;
	int *tmp;
	tmp = x;
	//task 인자값을 받아올 수 있음
	for(cnt = 1; cnt < *tmp; cnt++)
		printf("work form t2: %d * 2 = %d\n", cnt, cnt*2);

	printf("t2 finished\n");
}

int main(int argc, char *argv[])
{
	pthread_t A,B;
	int n1,n2;

	if(argc != 3)
	{
		printf("Usage: exe t1_num t2_num\n");
		exit(-1);
	}

	n1 = atoi(argv[1]); //atoi -  ascii to intiger
	n2 = atoi(argv[2]);

	//pthread_create(id, ?, task name, task 인자)
	pthread_create(&A, NULL, t1, &n1);
	pthread_create(&B, NULL, t2, &n2);

	pthread_join(A, NULL);
	pthread_join(B, NULL);

	return 0;
}



