#include <stdio.h>
// char **argv의 인자 구분은 space bar로 구분
int main(int argc, char **argv)
{
	int i;
	for(i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
	return 0;
}
