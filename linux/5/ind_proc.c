#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int a = 10;

	printf("&a = %p\n",&a);

	sleep(1000);
	//process가 종료되면 kernel heap의 해당 process의  task_struct공간이 free된다.
	return 0;
}
