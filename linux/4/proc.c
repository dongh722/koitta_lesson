#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("befor\n");

	fork(); //분신
	
	printf("after\n");

	return 0;
}
