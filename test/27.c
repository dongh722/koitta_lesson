#include <stdio.h>

//void (*)(void) (*)(void (*)(void)) (*)(void (*)(void)) (*)(void)

//void (*)(void) (*)(void (*)(void)) (*(*)(void))(void (*)(void))
//void (*)(void) (*(*(*)(void))(void (*)(void)))(void (*)(void))


//void (*(*(*)(void (*)(void)))(void (*)(void)))(void)
//void (*(*)(void (*)(void))(void)

//void (*(*(*(*)(void))(void (*)(void)))(void (*)(void)))(void)

int hi1(void)
{
	printf("1\n");
	return 1;
}

int hi2(void)
{
	printf("2\n");
	return 2;
}

int (*(hi3(int (*p)(void))))(void)
{
	printf("3\n");
	p();
	return hi2;
}

int (*(*(hi4(int (*p2)(void))))(int (*p)(void)))(void)
{
	printf("4\n");
	p();
	p2();
	return hi3;
}


int (*(*(*(hi5(void))(int (*p2)(void)))(int (*p)(void))))(void)
{
	printf("5\n");
	p();
	p2();
	return 	hi4;
}

int main(void)
{
	int res=0;
	res = hi5()(hi1)(hi2)();

	printf("res =%d\n",res);
	return 0;
}
