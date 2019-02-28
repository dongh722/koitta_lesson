#include <stdio.h>

void test(void)
{
	printf("test\n");
}

int num_test(void)
{
	printf("num_test\n");
	return 7;
}

// int(*)(void) test_test(void (*p)(void))
int (* test_test(void (*p)(void)))(void)
{
	printf("test_test\n");
	p();
	return num_test;
}

//int (*)(void) (*) (void (*)(void)) resturn type
//void (*p)(void) 인자 타입

//int (*)(void) *pof_test(void(*p)(void)) (void (*)(void))
int (*(*pof_test(void(*p)(void)))(void (*)(void)))(void)
{
	printf("pof_test\n");
	p();		
	return test_test;
}

int main(void)
{
	int res = pof_test(test)(test)();
	printf("res = %d\n",res);
	return 0;
}
