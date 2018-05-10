
#include "wrapsock.h"

static int read_cnt;  //how many chars were readed from socket stream
static char *read_ptr; //current read position in read buffer
static char read_buff[MAXLINE]; //read buffer

int  Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n;

again:
	if ((n = accept(fd, sa, salenptr)) < 0)
	{
#ifdef EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif // EPROTO
			goto again;
		else
			err_sys("accept error");
	}
	return (n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		err_sys("bind error");
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0)
		err_sys("connect error");
}

void Listen(int fd, int backlog)
{
	char   *ptr;

	/*4can override 2nd argument with environment variable */
	if ((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);
	if (listen(fd, backlog) < 0)
		err_sys("listen error");
}

int Socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		err_sys("socket error");
	return (n);
}

/* include readn*/
static ssize_t my_read(int fd, char *ptr)
{
	if (read_cnt <= 0) { // read_buff is empty 
	again:
		if ((read_cnt = read(fd, read_buff, sizeof(read_buff))) < 0) { //read new chunk of data
			if (errno == EINTR) //function read() was interupted
				goto again;  //try to read new chunk of data
			return -1; // error 
		}
		else if (read_cnt == 0) // EOF
			return (0);
		read_ptr = read_buff; // reset read pointer to begin of the read buffer
	}

	read_cnt--; // 1 char from read buffer readed
	*ptr = *read_ptr++; //set current char from buffer to ptr
	return (1); // return 1 , succes
}
ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t		n, rc;
	char		c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) { // 1 char is for terminating '\0'
		if ((rc = my_read(fd, &c)) == 1) { //we readed 1 char
			*ptr++ = c; //write this char to caller buffer , and go to next char position
			if (c == '\n')
				break; /* new line is stored,like fgets() */
		}
		else if (rc == 0) {
			*ptr = 0; //set terminating '\0'
			return (n - 1); /* EOF, n - 1 bytes were read*/
		}
		else
			return (-1); /* error, errno set by read() */
	}

	*ptr = 0; /* null terminate like fgets() */
	return (n);
}
ssize_t readlinebuf(void **vptrptr)
{
	if (read_cnt)
		*vptrptr = read_ptr;
	return (read_cnt);
}

/*end readline*/

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
	ssize_t		n;
	if ((n = readline(fd, ptr, maxlen)) < 0) /* -1 error */
		err_sys("readline error");
	return (n);
}

/* include writen */
ssize_t writen(int fd, const void *vptr, size_t n) /*Write "n" bytes to a descriptor. */
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while ( nleft > 0)
	{
		if ((nwritten = write(fd, ptr, nleft)) < 0)
		{
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;   /* and call write() again */
			else
				return (-1);    /* error */
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return (n);
}
/* end writen */

void Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
	{
		if (errno == EPIPE)
		{
			puts("EPIPE error");
			puts(strerror(errno));
			exit(EXIT_FAILURE);
		}
		else
		{
			err_sys("writen error");
		}
		
	}
		
}