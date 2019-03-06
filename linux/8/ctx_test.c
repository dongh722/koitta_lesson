#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

//실행 보장이 안되는 코드

void print_str(char *str)
{
	while(*str != '\0')
	{
		putchar(*str++);
		fflush(stdout);
	}
}

int main(void)
{
	if(!fork())
	{
		print_str("-------------------\n");
	}
	else
	{
		print_str("+++++++++++++++++++\n");
	}

	return 0;
}
