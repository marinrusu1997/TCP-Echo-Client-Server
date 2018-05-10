#pragma once

#ifndef __WRAP_UNIX_H__
#define __WRAP_UNIX_H__

#include <unistd.h>
#include <sys/types.h>
#include "error.h"
#include <signal.h>


typedef void Sigfunc (int);

void  Close(int fd);
pid_t Fork(void);
Sigfunc * Signal(int signo, Sigfunc *func);

#endif // !__WRAP_UNIX_H__

