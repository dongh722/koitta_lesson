#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv)
{
	char ch;
	char perm[11] = "-----------";
	struct passwd *pw; //user 구조체
	struct group *gr; //group 구조체
	struct stat buf;	//파일 종류 정보
	char rwx[4] = "rwx"; //실행 권한 정보
	char sst[4] = "sst";	//chmod 4xxx 첫번재 s set uid
							//chmod 2xxx 두번째 s set groupid
							//chmod 1xxx 세번째 t 스티키비트(폴더 : 공유 , 파일 :
	int i;

	if(argc !=2)
	{
		printf("Usage: exefile filename or dirname\n");
		exit(-1);
	}

	stat(argv[1], &buf);

	//파일 종류 정보
	if(S_ISDIR(buf.st_mode))
		perm[0] = 'd'; //derectory
	else if(S_ISREG(buf.st_mode))
		perm[0] = '-'; //일반 파일
	else if(S_ISFIFO(buf.st_mode))
		perm[0] = 'p'; //pipe 파일
	else if(S_ISCHR(buf.st_mode))
		perm[0] = 'c'; //charactor disk (연속적에 데이터 처리의 디바이스 드라이버) ex 카메라
	else if(S_ISBLK(buf.st_mode))
		perm[0] = 'b'; //block disk (ram,과 하드디스크와 같은 연속적이지 않은 정보 처리 디스크 드라이버)

	for(i = 0; i < 9; i++)
	{
		//buf.st_mode 16bit로 구성 하위 9bit구성은(rwxrwxrwx)이다.
		//										  (123456789)
		if((buf.st_mode >> (8-i)) & 1)
		{
			perm[i+1] = rwx[i % 3];
		}
	}

	for(i = 0; i <3; i++)
	{
		if((buf.st_mode >>(11-i)) &1)
		{
			if(perm[(i + 1) * 3] == '_')
			{
				perm[(i + 1) *3] = sst[i] ^ 0x20;//실행권한이 없을 때 대문자
			}
			else
			{
				perm[(i + 1) * 3] = sst[i]; //실행권한이 있을 때 대문자
			}
		}
	}

	printf("%s ", perm);
	//ex)drwxr-xr-x 처음 rwx자리는 소유자가 가능한 권한 저보 두번째 rwx자리 xr은 그룹의 권한 정보자리 세번째 rwx는 제 3자	


	pw = getpwuid(buf.st_uid);
	printf("%s ", pw->pw_name);//uid 소유자  권한 정보 User가 만든거라면 사용자 이름이 붙음 ex-koitta 참고 :root 최고 권한

	gr = getgrgid(buf.st_gid); //그룹 관리자 정보 사용자가 만든 것은
	printf("%s\n",gr->gr_name);

	return 0;
}
