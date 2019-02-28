#include <stdio.h>
#include<time.h>
#include<stdlib.h>

int init_rand(void)
{	
	int res;
	srand(time(NULL));
	
	res = rand() %10 +1;
	printf("res = %d\n",res);

	return res;
}

void init_arr(int arr[10], int num)
{
	int i;
	for( i =0; i<num; i++)
		arr[i] = i;
}

void print_arr(int arr[10], int len)
{
	int i;
	for(i=0;i<len;i++)
		printf("arr[%d] = %d\n", i, arr[i]);
}
int main(void)
{
	int i;
	int arr[10] = {0,};
	for(i=0;i<10;i++)
		printf("arr[%d] = %d\n", i, arr[i]);
	init_arr(arr,init_rand());
	print_arr(arr, sizeof(arr)/sizeof(int));
	return 0;
}
