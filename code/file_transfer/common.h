#ifndef _COMMON_H
#define _COMMON_H

#define _POSIX_C_SOURCE	200809L
#define _XOPEN_SOURCE	700

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

/* Standard headers */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFLEN		160000
#define SERVER_PORT	"60000"

/* Default file access permissions for new files */
#define FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#endif
