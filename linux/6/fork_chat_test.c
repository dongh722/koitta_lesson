#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd, ret;
	char buf[1024];
	pid_t pid;

	fd = open("myfifo", O_RDONLY);

	if((pid = fork()) > 0 )	
	//fork - 부모 메모리를 복사하여 자식 메모리에 붙여넣기
	//demand on Paging : 요청에 의한 paging. kernel에서 sagmentation 오류가 나면 물리메모리가 부족한 것이므로 paging 요청을 보내게 된다.
	// 이 기능을 사용하기 위해서 fork를 사용한다. 이것을 사용하면 두개의 개별 프로세스를 사용할 때보다 빠르다
	{
		for(;;)
		{
			ret = read(0,buf, sizeof(buf));
			buf[ret] = 0;
			printf("Keyboard : %s\n", buf);
		}
	}
	else if(!pid)
	{
		for(;;)
		{
			ret = read(fd, buf, sizeof(buf));
			buf[ret] = 0;
			printf("Pipe : %s\n", buf);
		}
	}
	else
	{	
		perror("fork() ");
		exit(-1);
	}

	close(fd);

	return 0;
}
