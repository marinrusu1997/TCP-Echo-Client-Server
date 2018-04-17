#pragma once

#ifndef __WRAP_SOCK_H__
#define __WRAP_SOCK_H__

#include "error.h"
#include <netinet/ip.h>
#include <unistd.h>

#define SA struct sockaddr

int  Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Listen(int fd, int backlog);
int  Socket(int family, int type, int protocol);
ssize_t Readline(int fd, void *ptr, size_t maxlen);
void Writen(int fd, void *ptr, size_t nbytes);


#endif // __WRAP_SOCK_H__
