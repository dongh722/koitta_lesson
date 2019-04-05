#define _GNU_SOURCE
#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


//스레드는 스레드 그룹아이디(tgid)는 같지만 pid(process id)는 다르다.
//스레드는 메모리를 공유한다.

void *test(void *none)
{
	printf("tgid(%lu), pid(%lu): thread\n", getpid(), syscall(__NR_gettid));
}

int main(void)
{
	int tid;
	pthread_t thread;
	pid_t pid = fork();

	// 참고 getpid() = tgid 얻어오는 함수 syscall(__NR_gettid) = pid 값 얻어오기
	if(!pid)
		printf("tgid(%d), pid(%d): child\n", getpid(), syscall(__NR_gettid));
	else
		printf("tgid(%d), pid(%d): parent\n", getpid(), syscall(__NR_gettid));

	tid =  pthread_create(&thread, NULL, test, NULL);
	pthread_join(thread, NULL);

	return 0;
}
