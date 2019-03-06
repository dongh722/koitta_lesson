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
	int serv_sock, clnt_sock;

	si serv_addr;
	si clnt_addr;
	socklen_t clnt_addr_size;

	char msg[] = "Hello Network Programming~~!!~!\n";

	if(argc != 2)
	{
		printf("Usage: %s <port>\n",argv[0]);// PORT는 65535개 특수 사용 포트 불가능(ex 80번 포트)
		exit(-1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM,0); //소켓 생성

	if(serv_sock == -1)
		err_handler("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr)); //serv_addr 구조체 변수 공간 초기화
	serv_addr.sin_family = AF_INET; //TCP 사용
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));//setting port

	if(bind(serv_sock, (sap) & serv_addr, sizeof(serv_addr)) == -1)// socket에 ip주소와  포트 번호 연결(커널에서 알아서)
		err_handler("bind() error");
	if(listen(serv_sock,10) == -1) //client 받을 수 있도록 설정
		err_handler("listen() error");
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock =  accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size); //client 연결 대기

	if(clnt_sock == -1)
		err_handler("accept() error");
	write(clnt_sock,msg,sizeof(msg)); //client 쓰
	close(clnt_sock);
	close(serv_sock);

	return 0;
}
