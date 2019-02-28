#include <stdio.h>

// void(*)(void)
void test(void)
{
	printf("test\n");
}

// void(*)(void) test_test(void);
void (* test_test(void))(void)
{
	printf("test_test\n");
	return test;
}

int main(void)
{
	test_test()();
	
	return 0;
}
