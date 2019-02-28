#include <stdio.h>

int func(int *num);


int main(void)
{
	int res;
	int num[4] = {1,2,3,4};
	
	res =func(num);
	printf("respond = %d\n",res);
	return 0;
}

int func(int *num)
{
	int temp=0;
	for(int i=0; i<4;i++) temp +=*(num++);
	return temp;
}
