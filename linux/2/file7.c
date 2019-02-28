#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	off_t new_pos;
	char wbuf[32] = "test test test";
	char rbuf[32] = "";

	fd = open("reading.txt", O_RDWR); //참고 : open의 설명을 읽고 싶다면 man -s2 opn
	new_pos =  lseek(fd,(off_t)10, SEEK_SET);
	printf("new_pos = %ld\n", new_pos);
	read(fd, rbuf, sizeof(rbuf));//읽은 위치까지 pos이동
	printf("rbuf = %s\n",rbuf);
	close(fd);
	return 0;
}
