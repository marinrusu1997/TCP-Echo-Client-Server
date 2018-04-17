#pragma once

#ifndef __WRAP_UNIX_H__
#define __WRAP_UNIX_H__

#include <unistd.h>
#include <sys/types.h>
#include "error.h"

void  Close(int fd);
pid_t Fork(void);

#endif // !__WRAP_UNIX_H__

