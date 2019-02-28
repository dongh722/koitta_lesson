#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int init_rand(void)
{	int res;

	res = rand() % 9  +1;
	return res;
}

void init_arr(int arr[100])
{
	int cnt;
	for(cnt=0;cnt<100;cnt++)
		arr[cnt] = init_rand();
}

void print_arr(int arr[],int len)
{
	int cnt_i;

	for(cnt_i = 1; cnt_i<len +1; cnt_i++)
	{
		printf("%3d",arr[cnt_i-1]);

		if(!(cnt_i %10))
		{
			printf("\n");
		}
	}
	printf("\n");
}

bool Cnt_arr(int arr[],int cnt_arr[],int cnt)
{
	int cnt_i,cnt_j;
	cnt=0;
	for(cnt_i=0;cnt_i<100;cnt_i++)
	{
		cnt_arr[arr[cnt_i]-1]++;
	}
	
	for(cnt_i=0;cnt_i<9;cnt_i++)
	{
		printf("%4d",cnt_arr[cnt_i]);
	}
	
	printf("\n");
	for(cnt_i=0; cnt_i<9;cnt_i++)
	{
		for(cnt_j=(cnt_i+1);cnt_j<9;cnt_j++)
		{
			if(cnt_arr[cnt_i]==cnt_arr[cnt_j])
			{
				memset(cnt_arr,0x0,40);
				cnt++;
				return 1;
			}
		}
	}

	return 0;
}

void List_num(int arr[9])
{	
	int cnt_i,cnt_j,cnt_k,cnt=0;
	int aList[3] ={0,};
	int aList_cnt[3] ={0,};
	for(cnt_i=0;cnt_i<9;cnt_i++)
	{
		for(cnt_j=0;cnt_j<9;cnt_j++)
		{
			if((arr[cnt_i]-arr[cnt_j])>0) cnt++;
		}

		if(cnt==8)
		{
			aList[0] = cnt_i+1;
			aList_cnt[0]=arr[cnt_i];
		}
		else if(cnt==7)
		{
			aList[1] =cnt_i+1;
			aList_cnt[1] = arr[cnt_i];
		}
		else if(cnt==6)
		{
			aList[2] =cnt_i+1;
			aList_cnt[2] =arr[cnt_i];
		}
		cnt =0;
			
	}

	printf("num = %d, count = %d\n",aList[0],aList_cnt[0]);
	printf("num = %d, count = %d\n",aList[1],aList_cnt[1]);
	printf("num = %d, count = %d\n",aList[2],aList_cnt[2]);
	
}

int main(void)
{
	int cp =0;;
	int num[9] ={1,2,3,4,5,6,7,8,9};
	int arr[100] ={0,};
	int cnt_arr[9] ={0,};

	srand(time(NULL));
	init_arr(arr);
	while(Cnt_arr(arr,cnt_arr,cp))
	{
		init_arr(arr);
	}

	printf("%d\n",cp);
	print_arr(arr,100);

	print_arr(num,9);	
	print_arr(cnt_arr,9);

	List_num(cnt_arr);
	return 0;
}

