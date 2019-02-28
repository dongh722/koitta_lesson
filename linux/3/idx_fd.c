#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(void)
{
	DIR *dp;
	int i = 0;
	struct dirent *p;

	dp = opendir(".");
	

	while(p = readdir(dp))
	{
		//dirent
		//d_ino -derectory link 정보
		//d_name - directory 내부 이름
		if(p->d_name[0] == '.') //숨김파일 넘김(보여주지 않음)
			continue;
		printf("%-12s ",p->d_name);//12칸을 보장한다.

		if((i+1) % 5 == 0)
			printf("\n");

		i++;
	}

	printf("\n");
	closedir(dp);

	return 0;
}
