#include <stdio.h>

int range(int data)
{
	return data & (-(1<<27));
}

int main(void)
{
	int i=0;
	int array[5] = {(1<<27)+1,(1<<29)-1,6,50000,(1<<20)+1};

	printf("array data = ");
	for(i=0;i<5;i++)
		printf("%d, ",array[i]);

	printf("\nafter range\n");
	printf("array data = ");
	for(i=0;i<5;i++)
	{
		array[i] =range(array[i]);
		printf("%d, ",array[i]);
	}

	printf("\n");
}
