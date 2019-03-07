#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 2400

typedef struct sockaddr_in si;
typedef struct sockaddr * sap;

void err_handler(char *msg)
{
	fputs(msg, stderr);
	fputs('\n',stderr);
	exit(1);
}

int main(int argc, char **argv)
{
    int sock;
    int str_len;
    si serv_addr;
    char msg[32];
	char *m =  "input msg(q to quit): ";

    if(argc != 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(-1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0); //socket 생성

    if(sock == -1)
        err_handler("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; //TCP
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); //ip
    serv_addr.sin_port = htons(atoi(argv[2]));  //port

    if(connect(sock, (sap)&serv_addr,sizeof(serv_addr))== -1)   //서버 연결
        err_handler("connect() error");
	else
		puts("Sucess to Connection");

	for(;;)
	{
		fputs("input msg(q to quit): ", stdout);
		fgets(msg, BUF_SIZE, stdin);
		if(!strcmp(msg,"q\n") ||!strcmp(msg, "Q\n"))
			break;
		write(sock, msg, strlen(msg));
    	str_len =read(sock, msg, sizeof(msg) -1); //읽어오기

    	if(str_len == -1)
        	err_handler("read() error");
		msg[str_len] = 0;

    	printf("msg from server: %s\n",msg);
	}

    close(sock);
    return 0;
}
