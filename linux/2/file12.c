#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//rm
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: exename del_file\n");
		exit(-1);
	}

	unlink(argv[1]);
	return 0;
}
