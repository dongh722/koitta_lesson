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
	return 0;
}
