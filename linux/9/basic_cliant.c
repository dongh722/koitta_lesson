#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); //ip 참고 :inet_addr(ip문자열) ipv4의 문자열을 4바이트 정수값의 ip주소로 변경
    serv_addr.sin_port = htons(atoi(argv[2]));  //port

    if(connect(sock, (sap)&serv_addr,sizeof(serv_addr))== -1)   //서버 연결
        err_handler("connect() error");
    str_len =read(sock, msg, sizeof(msg) -1); //읽어오기

    if(str_len == -1)
        err_handler("read() error");

    printf("msg from server: %s\n",msg);
    close(sock);

    return 0;
}
