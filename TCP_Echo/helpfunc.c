
#include "helpfunc.h"
#include <sys/wait.h>

/* c - upper case letter
   returns -1 if c is not a letter , on succes uppercase letter
*/
inline char lower(char c)
{
	/*
		Bynary OR '|' operator copies a bit if it exists in either operand
		eg : A = 0x41 , B = 0x20 -> A | B = 0x61
			A = 0100 0001 , B = 0010 0000 -> A | B = 0110 0001
	*/
	if ((c >= 0x41) && (c <= 0x5A)) /* ASCII Table : 0x41 <-> 0x5A == A <-> Z */
		return c | 0x20; /* lower case letters are 0x20 apart from upper case letters */
	if ((c >= 0x61) && (c <= 0x7A)) /* ASCII Table : 0x61 <-> 0x7A == a <-> z*/
		return c; /* c is already in lower case */
	return -1; /* error, c is not a letter */
}
/*
	c - lower case letter
	returns -1 if c is not a letter , on succes lower case letter
*/
char upper(char c)
{
	/*
		Binary XOR Operator copies the bit if it is set in one operand but not both
		eg : A = 0x7A , B = 0x20 -> A ^ B = 0x5A
			A = 0111 1010 , B = 0010 0000  -> A ^ B = 0101 1010
	*/
	if ((c >= 0x61) && (c <= 0x7A)) /* ASCII Table : 0x61 <-> 0x7A == a <-> z*/
		return c ^ 0x20; /* upper case letters are 0x20 apart from lower case letters */
	if ((c >= 0x41) && (c <= 0x5A)) /* ASCII Table : 0x41 <-> 0x5A == A <-> Z */
		return c; /* c is already in upper case */
	return -1; /* error, c is not a letter */
}

void str_echo(int sockfd)
{
	ssize_t    n;
	char       buff[MAXLINE], lowerBuff[MAXLINE], c;
	char	   *append, *ismaxim;
	long	   arg1, arg2;

	//again:
	//	while ((n = read(sockfd, buff, MAXLINE)) > 0)
	//		Writen(sockfd, buff, n);
	//
	//	if (n < 0 && errno == EINTR)
	//		goto again;
	//	else if (n < 0)
	//		err_sys("str_echo: read error");

	for (;;)
	{
		if ((n = read(sockfd, buff, MAXLINE)) <= 0)
			return;

		int buff_size = strlen(buff);
		for (int i = 0; i < buff_size; i++)
			if ((c = lower(buff[i])) != -1)
				lowerBuff[i] = c;

		if ((ismaxim = strstr(lowerBuff, "maxim")) != NULL)
		{
			Writen(sockfd, "A Maxim,pashol nahui!\n", strlen("A Maxim,pashol nahui!\n"));
			/*dont forget '\n',client expecting to read a line*/
			bzero(lowerBuff, sizeof(lowerBuff));
		}
		else
		{
			if (sscanf(buff, "%ld%ld", &arg1, &arg2) == 2) /* on succes sscanf returns the number of args specified */
			{
				snprintf(buff, sizeof(buff), "%ld\n", arg1 + arg2);
				Writen(sockfd, buff, strlen(buff));
				bzero(buff, sizeof(buff));
			}
			else
			{
				if ((append = getenv("ECHOAPPEND")) != NULL && strlen(append) < SRVMAXLINEOFFSET)
					Writen(sockfd, append, strlen(append));
				Writen(sockfd, buff, n);
				bzero(buff, sizeof(buff));
			}
		}

	}
}

void sigh_child(int signo)
{
	pid_t pid;
	int	  stat;

	//pid = wait(&stat);
	//pid = waitpid(-1, &stat, 0); --unsafe,will proces only first signal,UNIX dont have queue of signals
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated , with status %d\n", pid, stat);
	return;
}