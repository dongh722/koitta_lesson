#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RANGE 50
#define SAMPLE 10000000
#define DATA_MAX RAND_MAX

int *get_rand(void)
{
	int i;
	int *values = (int *)calloc(SAMPLE,sizeof(int));

	if(values)
	{
		for(i = 0; i<SAMPLE;i++)
		{
			values[i] = rand();
		}
	}

	return values;
}

int histogram(unsigned int *data)
{
	int i =0;
	int j =0;
	float percen =0;
	unsigned int cnt_ar[RANGE]={0,};

	for(i = 0; i<SAMPLE; i++)
	{
		for(j=1 ; j<=RANGE;j++)
		{
			if(*(data+i)>(unsigned int)(((unsigned int)DATA_MAX/RANGE)*(RANGE-j)))
			{
				cnt_ar[RANGE-j]++;
				break;
			}
		}
	}

	for(i= 0;i<RANGE;i++)
	{
		printf("%2d : ",i+1);

		percen = (float)(cnt_ar[i]*100)/(float)SAMPLE;

		for(j=0;j<percen*10;j++)
		{
			printf("*");
		}
//		printf("%d\n",cnt_ar[i]);
		printf(" %f%%",percen);
		printf("\n");
	}
}

int main(void)
{
	int i =0;
	unsigned int *data = NULL;

	srand(time(NULL));

	data = get_rand();

	histogram(data);

	return 0;
}
