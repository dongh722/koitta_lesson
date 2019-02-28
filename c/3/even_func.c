#include <stdio.h>
#include <stdbool.h>

bool is_it_bool(int value)
{
	if(value % 2)
		return false;
	else
		return true;
}

int main(void)
{
	if(is_it_bool(3))
		printf("이것은 짝수 입니다\n");
	else
		printf("이것은 홀수 입니다\n");
	return 0;
}
