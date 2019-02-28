#include <stdio.h>

int cnt =0;
int fib(int n)
{
	cnt++;
	if(n<=2)
		return 1;
	else
		return fib(n-1)+fib(n-2);
}

int main(void)
{
	int res;
	res = fib(5);
	printf("res = %d\n", res);
	printf("cnt = %d\n", cnt);
	return 0;
}
