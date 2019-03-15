#include <stdio.h>

unsigned long func(int num)
{
	unsigned long data =1;
	unsigned long tmp[2] ={0,0};
	if(num>2)
	{
		while(num-1)
		{
			tmp[1] = tmp[0];
			tmp[0] =data;
			data = tmp[1] +tmp[0];
			num--;
		}
	}
	return data;
}

unsigned long sum(unsigned long *arr)
{
	int i=0;
	unsigned long data=0;
	for(i=0;i<57;i++)
	{
		data =func(i+1);

		printf("%lu, ",data);

		if(!((i+1)%10))
			printf("\n");

		if(data % 2)
			arr[0] += data;
		else
			arr[1] += data;
	}
}

int main(void)
{
	unsigned long arr[2]={0,0};
	sum(arr);

	printf("\neven sum = %lu\n",arr[1]);
	printf("odd sum = %lu\n",arr[0]);

	return 0;
}
