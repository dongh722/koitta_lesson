#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int rand_init(void)
{
	srand(time(NULL));
	return rand() % 3 + 1;
}

int switch_test(int num)
{
	switch(num)
	{
		case 1:
			printf("1 Detected\n");
			break;
		case 2:
			printf("2 Detected\n");
			break;
		default:
			printf(" wrong Number\n");
			break;
	}
}

int main(void)
{
	int num = rand_init();
	printf("num = %d\n", num);
	switch_test(num);

	return 0;
}

