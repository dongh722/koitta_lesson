//goto는 다중 루프를 빠져나올때 유용한 문법이다. 그러나 이것는 함수 내에서만 동작하며 다른 함수로 이동은 불가능한다.
// 이는setjmp와 longjmp를 통해 가능하다.

#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <setjmp.h>
#include <unistd.h>

jmp_buf env;
void error(int a);

int main(void)
{

	int ret =0;
	char buf[1024] ={0,};
	signal(SIGINT, error);
	
	if(!(ret = setjmp(env)))
		for(;;)
		{
			read(0,buf,sizeof(buf));
			write(1,buf,sizeof(buf));

		}
	return 0;
}

void error(int a)
{
	printf("error\n");
	longjmp(env,1);
}
