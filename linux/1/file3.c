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
	strcpy("Hellow Linux System Programming!\n",text);
	fd = open("text.txt", O_CREAT | O_WRONLY, 0644); //text.txt 생성하고 읽고 쓰기  -rw-r--r--와 같은 권한 부여
	printf("fd = %d\n", fd);
	
	nw = write(fd, text, strlen(text)); //text.txt 파일에 text 문자열 쓰기
	printf("nw = %d\n",nw);

	write(fd,"\0",1);
	close(fd);
	return 0;
}
