#include "wrappers.h"
#include "helpfunc.h"
#include "sockfuncs.h"
#include <strings.h>


#define BUFFLEN 1024


int main()
{


	int			listenfd, connfd;
	pid_t		childpid;
	socklen_t	clilen;
	struct sockaddr_in cliaddr, servaddr;
	char buff[BUFFLEN];
	void		sigh_child(int);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sigh_child);

	printf("Listening ... \n %d \n", SERV_PORT);


	for (;;)
	{
		clilen = sizeof(cliaddr);
		//connfd = Accept(listenfd, (SA*)&cliaddr, &clilen); --not safe, interrupt will cause error
		//getchar();
		if ((connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) < 0)
			if (errno == EINTR)
				continue;
			else
				err_sys("accept error");

		fflush(stdout);
		printf("\n New incomming connection from : %s:%d ", 
			Inet_ntop(cliaddr.sin_family, &cliaddr.sin_addr, buff, clilen),cliaddr.sin_port);
		fflush(stdout);
		//signal(SIGCHLD, sigh_child);

		if ((childpid = Fork()) == 0) /* child process */
		{ 		
			Close(listenfd); /* closing listen file descriptor for child process */
			str_echo(connfd); /* handle request */
			exit(0);
		}
		Close(connfd); /* parent process closing connected socket */
	}

	return 0;
}