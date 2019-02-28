#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd;// 0 표준입력 1 표준출력 2 에러
	fd = open("test.txt", O_CREAT); //파일 생성(cf 디렉토리도 파일)
	printf("fd = %d\n",fd);
	return 0;
}
