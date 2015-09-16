#include "common.h"

/* Read "n" bytes from a descriptor */
ssize_t
readn(int fd, void *ptr, size_t n)
{
	size_t nleft;
	ssize_t nread;

	nleft = n;
	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (nleft == n)
				return -1;	/* error, return -1 */
			else
				break;		/* error, return amount read so far */
		} else if (nread == 0) {
			break;
		}

		printf("Read %zu bytes\n", nread);
		nleft -= nread;
		ptr += nread;
	}

	return (n - nleft);	/* return >= 0 */
}

/* Write "n" bytes to a descriptor */
ssize_t
writen(int fd, void *ptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;

	nleft = n;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) < 0) {
			if (nleft == n)
				return -1;	/* error, return -1 */
			else
				break;		/* error, return amount written so far */
		} else if (nwritten == 0) {
			break;
		}

		printf("Wrote %zu bytes\n", nwritten);
		nleft -= nwritten;
		ptr += nwritten;
	}

	return (n - nleft);	/* return >= 0 */
}


/* Set the SCTP stream parameters */
int
set_sctp_stream_params(int sockfd, int num_ostreams, int max_instreams)
{
	struct sctp_initmsg initmsg;

	memset(&initmsg, 0, sizeof initmsg);
	initmsg.sinit_num_ostreams = num_ostreams;
	initmsg.sinit_max_instreams = max_instreams;

	return setsockopt(sockfd, IPPROTO_SCTP, SCTP_INITMSG,
			&initmsg, sizeof initmsg);
}
