#include <stdio.h>

void insert_range(int *arr,int len)
{
	int i,j,key,tmp;
	for(i=len-1;i>0;i--)
	{
		key=arr[i-1];

		for(j=i;arr[j]>key;j++)
		{
			
			arr[j-1] =arr[j];
		}
		arr[j-1]=key;
	}
}

int main(void)
{
	int i;
	int arr[20] ={1,3,7,2,4,8,5,20,17,9,18,19,16,11,12,15,13,10,6,14};

	printf("array =");
	for(i=0;i<20;i++)
		printf("%d, ",arr[i]);

	insert_range(arr,20);

	printf("\nafter range\n");
	
	printf("array =");
	for(i=0;i<20;i++)
		printf("%d, ",arr[i]);
	printf("\n");
}
