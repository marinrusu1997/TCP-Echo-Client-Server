#pragma once

#ifndef __CONFIG_PARAMS_H__
#define __CONFIG_PARAMS_H__


#ifdef MAXLINE
#undef MAXLINE
#define MAXLINE   4096 /* max text line length */ 
#else
#define MAXLINE   4096 /* max text line length */ 
#endif // MAXLINE

#define SERV_PORT 9877 /* TCP and UDP*/
#define SERV_PORT_STR "9877" /* TCP and UDP*/
#define LISTENQ   1024 /* 2nd argument to listen() */
#define SRVMAXLINEOFFSET 1000

#endif // !__CONFIG_PARAMS_H__
