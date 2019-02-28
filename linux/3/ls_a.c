#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define A_OPT 1
#define L_OPT 2
#define R_OPT 4

int main(int argc,char **argv)
{
	DIR *dp;
	int i = 1;
	int opt_flag = 0;
	int cmd =0;
	struct dirent *p;

	dp = opendir(".");//자기 자신의 dir

	while((cmd = getopt(argc, argv,"alR"))>0)
	{
		switch(cmd)
		{
			case 'a':
				opt_flag |= A_OPT;
				break;
			case 'l':
				opt_flag |= L_OPT;
				break;
			case 'R':
				opt_flag |= R_OPT;
				break;
			default:
				break;
		}
	}

	while(p = readdir(dp))
	{
		//dirent
		//d_ino -derectory link 정보
		//d_name - directory 내부 이름
		if(p->d_name[0] == '.')//앞에 이름에 .이 있으면 숨김파일
		{
			if(!(opt_flag & A_OPT))
			//숨김파일 넘김(보여주지 않음)
			continue;
		}
		printf("%-12s ",p->d_name);//12칸을 보장한다.

		if(!(i++ % 5))
			printf("\n");
	}

	printf("\n");
	closedir(dp);

	return 0;
}
