#include "helpfunccli.h"

void str_cli(FILE *fp, int sockfd)
{
	char     sendline[MAXLINE], recvline[MAXLINE + SRVMAXLINEOFFSET];

	while (Fgets(sendline, MAXLINE, fp) != NULL) //if ^D is tasted, fgets return's null pointer 
	{
		/* suppose that server process was killed */
		/* before we will appeal writen() TCP client will receive FIN segment from server TCP */
		/* we can write in socket that received FIN error , it is not an error */
		/* receiving FIN segment just means that server wont write anymore data in the canal */
		//Writen(sockfd, sendline, 1); /* after this writen() our socket will receive RST segment,we can't write anymore in this socket */
		//sleep(1);
		//int size_ = strlen(sendline) - 1;
		//Writen(sockfd, sendline + 1, strlen(sendline) - 1); /* we are trying to write in the socket that received RST sergment*/
															/* it's an error and process will receive signal SIGPIPE */
															/* if process will intercept signal and will return from signal handler */
															/* or will ignore SIGPIPE signal,write will return EPIPE error */
		/* 
			there are 2 ways solving this problem :	
				1) set SIG_IGN , assuming that next output operations will intercept EPIPE error and will quit
				2) set handler , if there are many sockets we can't know on which socket error ocured
					if we want to know on which socket write() returned error ,we need to ignore signal
					or return from signal handler and handle EPIPE error from write()
		*/
		Writen(sockfd, sendline, strlen(sendline));
		if (Readline(sockfd, recvline, MAXLINE) == 0) //returns 0 after receiving FIN segment from server, 0 in this case means EOF
			err_quit("str_cli: server terminated prematurely");

		Fputs("Output from server: ", stdout);
		Fputs(recvline, stdout);
	}
}