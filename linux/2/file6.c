#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	off_t new_pos;
	char buf[32] = "test test test";
	fd = open("reading.txt", O_RDONLY);
	new_pos = lseek(fd,(off_t)10, SEEK_END);//파일 길이 체크(엔드오브 파일까지 문자갯수에서 1추가),f_pos를 이동 및 반환(system call)
	printf("new_pos = %ld\n",new_pos);
	//write(fd, buf, sizeof(buf));
	close(fd);
	return 0;
}


