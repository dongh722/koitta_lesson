#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int init_num(void);
int check_num(int num, int c1, int c2);

int main(void)
{
	int num;
	
	srand(time(NULL));

	num = init_num();
	printf("num = %d\n", num);
	if(check_num(num,2,3))
		printf("이것은 2와 3의 배수\n");
	else
		printf("이것은 2혹은 3의 배수가 아님\n");
	
	return 0;
}

int init_num(void)
{
	return rand() % 33 +1;
}

int check_num(int num, int c1, int c2)
{
	if(!(num % c1) || !(num % c2))
		return true;
	else
		return false;
}
