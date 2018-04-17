#pragma once

#ifndef __HELP_FUNC_H__
#define __HELP_FUNC_H__

#include "wrapsock.h"
#include <sys/types.h>
#include "config_params.h"

void str_echo(int sockfd);
char lower(char c);
char upper(char c);

#endif // !__HELP_FUNC_H__


