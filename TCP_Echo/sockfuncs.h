#pragma once
#ifndef __SOCK_FUNCS_H__
#define __SOCK_FUNCS_H__

#include <sys/types.h>
#include <arpa/inet.h>
#include "error.h"

const char * Inet_ntop(int family, const void *addrptr, char *strptr, socklen_t len);
void Inet_pton(int family, const char *strptr, void *addrptr);

#endif // !__SOCK_FUNCS_H__

