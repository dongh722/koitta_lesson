#include <stdio.h>

#define IM ((int)1<<12)
#define COE (int)(IM-1)

int and_not(int num)
{
	return num & ~COE;
}

int main(void)
{
	int res;
	res = and_not(22221);
	printf("res = %d\n", res);
	res = and_not(4096);
	printf("res = %d\n", res);
	res = and_not(4562);
	printf("res = %d\n", res);
	res = and_not(6701);
	printf("res = %d\n", res);
	res = and_not(21);
	printf("res = %d\n", res);

	return 0;
}
