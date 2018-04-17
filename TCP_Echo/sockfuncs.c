#include "sockfuncs.h"

const char * Inet_ntop(int family, const void *addrptr, char *strptr, socklen_t len)
{
	const char *ptr;

	/*
		inet_ntop() return values :
		non-null pointer		succes
		NULL					error , errno set to indicate error
	*/

	if (strptr == NULL) /* check for old code */
		err_quit("NULL 3rd argument to inet_ntop");
	if ((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		err_sys("inet_ntop error"); /* sets errno */
	return ptr;
}

void Inet_pton(int family, const char *strptr, void *addrptr)
{
	int   n;

	/*
	     inet_pton() return values : 
		 1			succes
		 0			src does not contain a character string representing a
					valid network adress in the specified adress family
		 -1			af does not contain a valid adress family, errno set to EAFNOSUPPORT
	*/

	if ((n = inet_pton(family, strptr, addrptr)) < 0)
		err_sys("inet_pton error for %s", strptr); /* errno set */
	else if (n == 0)
		err_quit("inet_pton error for %s", strptr); /* errno not set */

	/* nothing to return */
}