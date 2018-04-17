#include "stdiowrappfunc.h"

void Fclose(FILE *fp)
{
	/*
		fclose() return values :
		0			succes
		EOF			error, errno is set to indicate error
	*/
	if (fclose(fp) != 0)
		err_sys("fclose error");
}

FILE* Fdopen(int fd, const char *type)
{
	FILE	*fp;

	/*
		fdopen() associates a stream with existing file descriptor
				 file descriptor will be closed when the sream created by fdopen() is closed
		FILE pointer			succes
		NULL					error , errno is set to indicate the error
	*/

	if ((fp = fdopen(fd, type)) == NULL)
		err_sys("fdopen error");

	return (fp);
}

char* Fgets(char *ptr, int n, FILE *stream)
{
	char	*rptr;

	/*
		fgets() reads in at most one less than size characters
				'\0' is stored after the last character in the buffer
		ptr		succes
		NULL	error
	*/
	/*
		ferror() tests error indicator for stream pointed by stream
		nonzero			error indicator is set
		0				error indicator is not set
	*/
	Fputs("Your input: ", stdout);
	if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		err_sys("fgets error");

	return (rptr);
}

FILE* Fopen(const char *filename, const char *mode)
{
	FILE	*fp;

	if ((fp = fopen(filename, mode)) == NULL)
		err_sys("fopen error");

	return (fp);
}

void Fputs(const char *ptr, FILE *stream)
{
	if (fputs(ptr, stream) == EOF) /* EOF returned on error , not negative number on succes */
		err_sys("fputs eror");
}