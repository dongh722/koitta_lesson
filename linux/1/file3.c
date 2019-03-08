#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd;
	int nw;
	char text[64] ={0,};
	scanf("Hellow Linux System Programming!\n",text);
	fd = open("text.txt", O_CREAT | O_WRONLY, 0644);
	printf("fd = %d\n", fd);
	
	nw = write(fd, text, strlen(text));
	printf("nw = %d\n",nw);

	write(fd,"\0",1);
	close(fd);
	return 0;
}
