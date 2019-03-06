#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void)
{
	int fd[3];
	int i;

	fd[0] = socket(PF_INET, SOCK_STREAM, 0); //sock_stream TCP(상대 상태 확인)
	fd[1] =	socket(PF_INET, SOCK_DGRAM, 0); //sock_dgram UDP(상대 상태 확인 x 통보)
	fd[2] = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC);

	for(i = 0; i < 3; i++)
		printf("fd[%d] = %d\n", i, fd[i]);
	for(i = 0; i < 3; i++)
		close(fd[i]);

	return 0;
}
