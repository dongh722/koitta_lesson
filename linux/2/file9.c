#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>



void skip_white_space(char *buf)

{
	int i;

	for(i = 0; buf[i] != ' '; i++)
		;
}



long replace_text(int rfd, int wfd, char *tstr, char *cstr)
{

	char buf[32] = {0};
	int tlen = strlen(tstr);
	int clen = strlen(cstr);
	int loop_cnt = 0;
	int find_cnt = 0;
	int backup = 0, flag;
	int idx;
	int nr;
	int i;

	while(nr = read(rfd, buf, sizeof(buf)))
	{

		for(i = 0; i < nr; i++)
		{

			if(!strncmp(&buf[i], tstr, tlen))
			{
				if(!flag)
				{
					write(wfd, buf, i);
					backup = i;
				}
				//lseek(wfd, (off_t)i + (32 * loop_cnt) - find_cnt, SEEK_SET);

				skip_white_space(buf);
				write(wfd, cstr, clen);
				write(wfd, &buf[i + tlen], 1);
				i += 4;
				find_cnt++;
				flag = 1;
			}
		}



		if(flag)
		{
			int spec_len = backup + (tlen + 1) * find_cnt;
			write(wfd, &buf[spec_len], nr - spec_len);
			flag = 0;
			continue; //해당 루프의 다음번 반복 위치로 제어를 전달.
		}

		write(wfd, buf, nr);
		loop_cnt++;

	}

}



int main(int argc, char **argv)
{
	int fd;
	int sfd;
	long pos;


	if(argc != 3)
	{
		printf("Usage: exe target_text changing_txt\n");
		exit(-1);
	}


	sfd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if((fd = open("reading2.txt", O_RDWR)) < 0)
	{
		printf("There are no reading2.txt\n");
		exit(-1);
	}

	pos = replace_text(fd, sfd, argv[1], argv[2]);

	close(fd);

	return 0;
}
/*
int main(void)
{
	int fd;
	off_t new_pos;
	char find_st[4] ="test";
	char chang_st[3] ="how";
	char *rd_con;
	fd = open("reading2.txt", O_RDWR);
}
off_t check_file_size(int fd)
{
	off_t tmp =0;
	tmp = lseek(fd,(off_t)0,SEEK_END);
	lseek(fd,(off_t)0,SEEK_SET);
	return tmp;
}
off_t find_string(int fd,char *find,int st_size,off_t file_size)
{
	int new_pos =0;
	char now_buf[32] ={0,};

	while(new_pos<file_size)
	{
		lseek(fd,(off_t)new_pos,SEEK_SET);
		read(fd,now_buf,st_size);
		printf("now_buf = %s\n",now_buf);
		if(!strncmp(find,now_buf,st_size))
		{
			new_pos+;
		else
			new_pos++;
	}
}
 
char *get_read_buf(off_t size)
{
	char *tmp = (char *)malloc(size);
	return tmp;
}*/
