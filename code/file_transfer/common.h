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

/* SCTP specific */
#include <netinet/sctp.h>
#define NUM_OSTREAMS	5
#define MAX_INSTREAMS	5


#define BUFLEN		160000
#define SERVER_PORT	"60000"


/* Default file access permissions for new files */
#define FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


ssize_t readn(int fd, void *ptr, size_t n);
ssize_t writen(int fd, void *ptr, size_t n);
int set_sctp_stream_params(int sockfd, int num_ostreams, int max_instreams);

#endif
