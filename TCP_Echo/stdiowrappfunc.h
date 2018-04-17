#pragma once
#ifndef __STDIO_WRAPP_FUNC_H__
#define __STDIO_WRAPP_FUNC_H__

#include <stdio.h>
#include "error.h"

void Fclose(FILE *fp);
FILE* Fdopen(int fd, const char *type);
char* Fgets(char *ptr, int n, FILE *stream);
FILE* Fopen(const char *filename, const char *mode);
void Fputs(const char *ptr, FILE *stream);

#endif // !__STDIO_WRAPP_FUNC_H__
