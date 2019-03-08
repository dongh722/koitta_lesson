#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd;
	fd = open("test.txt", O_CREAT,0644);// =open("test.txt",O_CREAT,S_IRUSER|S_IWUSER|S_IRGRP|S_IROTH)
	printf("fd = %d\n",fd);
	return 0;
}

/*
open 함수를 사용할 경우 필요한 header - fcntl.h, sys/stat.h, sys/types.h
open(경로,flag,mode)
flag는 해당 경로의 파일을 어떤식으로 처리할 것인지를 나타낸다
mode는 각 권한을 설정한다.
mode의 경우 8진수로 구성되며 3번재 자리는 user 권한 2번째 자리는 group권한 1자리는 기타권한에 해당한다.
mode를 설정할 수 있는 경우는 flag가 O_CREAT, O_TMPFILE의 경우에서만 이다.
mode의 4번째 자리는 특수한 경우에만 사용된다. 해당 비트를 셋하면 4,2의 경우는 기존 파일의 소유주의 USERID 또는 Group ID로 파일을 실행한다.
현재 파일의 사용자의 USER ID와 GROUP ID는 변경되지 않는다.

mode 4번째 자리에 1을 set하는 경우 이 비트를 sticky bit라 부른다. 현재에는 잘 사용하지 않지만 .임시 파일을 생성한다.
