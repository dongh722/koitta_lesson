#include <unistd.h>
#include <stdio.h>

int main(void)
{
	execlp("ls", "ls", "-a", "-l", 0);//현재 실행 파일 가상 메모리  text 영역 부분을 ls text로 변환
	printf("ls -al test Success\n");
	
	return 0;
}
