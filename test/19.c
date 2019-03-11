#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int array_init(int *arr,int len)
{
	int i=0;
	int j=0;

	for(i=0;i<len;i++)
	{
		arr[i] = rand()%4096 +1;
	}			
}
float empty_per(int *arr,int len)
{
	int i =0;
	int empty=0;
	double persent =0;
	printf("총 %d개공간에서 총",len);
	for(i=0;i<len;i++)
	{
		empty += 4096-arr[i];
	}

	return (float)(empty*100)/(float)(4096*len);
}

int main(void)
{
	int i;
	int array[100] ={0,};	

	srand(time(NULL));
	array_init(array,100);

	for(i=0;i<100;i++)
	{
		printf("%5d, ",array[i]);
		if(!((i+1)%10))
			printf("\n");
	}
	printf("\n");

	printf("%0.1f%% 만큼 공간낭비가 발생하였습니다.\n",empty_per(array,sizeof(array)/sizeof(int)));
	return 0;
}
