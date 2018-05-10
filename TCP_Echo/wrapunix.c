#define _XOPEN_SOURCE
#include "wrapunix.h"


void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}

pid_t Fork(void)
{
	pid_t   pid;

	if ((pid = fork()) == -1)
		err_sys("fork error");
	return (pid);
}

Sigfunc * signal(int signo, Sigfunc *func)
{
	struct sigaction	act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask); //face ca sigaction sa nu contina signale care sa fie maskate
	act.sa_flags = 0;
	if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/*	SunOS  4.x	*/
#endif // SA_INTERRUPT
	}
	else {
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;		/*  SVR4 , 44BSD  */	
#endif // SA_RESTART
	}
	if (sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}

Sigfunc * Signal(int signo, Sigfunc *func)
{
	Sigfunc *sigfunc;

	if ((sigfunc = signal(signo, func)) == SIG_ERR)
		err_sys("signal error");
	return sigfunc;
}