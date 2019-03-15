#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define R_SIZE 4096

long File_size(int fd)
{
	off_t f_pos;
	f_pos = lseek(fd,(off_t)0,SEEK_END);

	return f_pos;
}

void string_print(int fd)
{
	off_t f_pos,file_size =0;
	char rbuf[R_SIZE] ={0,};
	char *pbuf[R_SIZE] ={0,};

	char *tmp=NULL;
	int i;
	int  l_count =0;

	file_size = File_size(fd);
	f_pos = lseek(fd,(off_t)0,SEEK_SET);

	if(file_size > R_SIZE)
		;
	else
	{
		read(fd,rbuf,sizeof(rbuf));
		strtok(rbuf,"\n");

		pbuf[0] = rbuf;

		while((tmp = strtok(NULL,"\n")) != NULL)
		{
			pbuf[1+l_count++] = tmp;
		}

		printf("front 5:\n");
		for(i=0;i<5;i++)
			printf("%s\n",pbuf[i]);

		printf("\nrear 5:\n");
		for(i=0;i<5;i++)
			printf("%s\n",pbuf[l_count-4+i]);
	}
}

int main(void)
{
	int fd;
	fd = open("reading.txt",O_RDWR);

	string_print(fd);

	return 0;
}
