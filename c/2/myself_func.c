#include <stdio.h>

int cnt =0;

int fib(int n)
{
	int tmp, first =1, second =1;


	if(n<=2)
		 return 1;
	else
	{
		n -= 2; 	
		while(n--)
		{
			tmp = first + second;
			second = first;
			first = tmp;
		}
		return tmp;
	}	
}

int main(void)
{
	int res;
	res = fib(5);
	printf("res = %d\n", res);
	printf("call cnt = %d\n",cnt);
	return 0;
}
