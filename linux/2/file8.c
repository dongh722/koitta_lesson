#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	off_t new_pos;
	char wbuf[32] = "test test test";
	char rbuf[33] = {0,};

	fd = open("reading.txt", O_RDWR);
	new_pos =  lseek(fd,(off_t)10, SEEK_SET);
	printf("new_pos = %ld\n", new_pos);
	read(fd, rbuf, sizeof(rbuf)-1);
	new_pos = lseek(fd,(off_t)0,SEEK_CUR);
	printf("rbuf = %s\n", rbuf);
	printf("new_pos = %ld\n", new_pos);
	close(fd);
	return 0;
}
