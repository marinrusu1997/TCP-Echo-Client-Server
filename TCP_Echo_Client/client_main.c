
#include "wrappers.h"
#include "sockfuncs.h"
#include "helpfunc.h"
#include "helpfunccli.h"

void sigpipe_handler(int signal)
{
	puts("SIG_PIPE occured,return from handler");
}


int main(int argc,char* argv[])
{
	int i,sockfd[5];
	struct sockaddr_in servaddr;
	 
	if (argc != 2)
		err_quit("usage: TCP_Echo_Client.out <IPadress>");

	//struct linger lin;
	//lin.l_onoff = 1;
	//lin.l_linger = 10;

	//Signal(SIGPIPE, SIG_IGN); //--ignore sig pipe
	Signal(SIGPIPE, sigpipe_handler); //handling SIGPIPE signal

	//for (i = 0; i < 5; i++) {
		sockfd[0] = Socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);

		Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

		Connect(sockfd[0], (SA*)&servaddr, sizeof(servaddr));
	//	setsockopt(sockfd[i], SOL_SOCKET, SO_LINGER, (void*)(&lin), sizeof(lin));
	//}
		
	str_cli(stdin, sockfd[0]);

	exit(0);
}