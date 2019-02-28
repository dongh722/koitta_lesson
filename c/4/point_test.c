#include <stdio.h>

int main(void)
{
	int *p = NULL;
	int num = 3;
	p = &num;

	printf("num = %d\n", num);
	printf("*p  = %d\n", *p);

	return 0;
}	
