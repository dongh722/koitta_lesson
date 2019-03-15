#include <stdio.h>

int func(int num)
{
	if(num>2)
		return func(num-1)+func(num-2);
	else if(num>1)
		num+func(num-1);
	else
		num;
}

int main(void)
{
	printf("23번째 = %d\n",func(23));
}
