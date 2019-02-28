#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define A_OPT 1
#define L_OPT 2
#define R_OPT 3


//flag g
int main(int argc, char **argv)
{
	int cmd;
	int opt_flag = 0;

	int i = 0;
	int cmd;
	struct dirent *p;

	while((cmd = getopt(argc,argv,"alR"))>0)//옵션 입력을 얻는 함수
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
				opt_flag |= R_OPT;				break;
			default:
				printf("exe -a or l or R\n");
				break;
		}
	}

	printf("opt_flag = %d\n", opt_flag);
	return 0;
}
