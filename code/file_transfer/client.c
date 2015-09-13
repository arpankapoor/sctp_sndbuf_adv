#include "common.h"
#define MAXSLEEP 128

extern int readn(int, void *, size_t);
extern int writen(int, void *, size_t);

int connect_retry(int domain, int type, int protocol,
		const struct sockaddr *addr, socklen_t alen)
{
	int numsec, fd;

	/* Try to connect with exponential backoff */
	for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
		if ((fd = socket(domain, type, protocol)) < 0)
			return -1;
		if (connect(fd, addr, alen) == 0)
			return fd;
		close(fd);

		/* Delay before trying again */
		if (numsec <= MAXSLEEP/2) {
			fprintf(stderr,
				"Connection failed, sleeping for %d secs\n",
				numsec);
			sleep(numsec);
		}
	}

	return -1;
}

void
rcv_file(int sockfd, int fd)
{
	ssize_t read;
	char buf[BUFLEN];

	while ((read = readn(sockfd, buf, BUFLEN)) > 0)
		writen(fd, buf, read);
}

int
main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addrinfo hints;
	int sockfd = -1,
	    fd = -1,
	    ret = -1,
	    err;

	if (argc != 3) {
		fprintf(stderr, "usage: %s HOSTNAME FILENAME_TO_SAVE_AS\n",
				argv[0]);
		goto errout;
	}
	if ((fd = open(argv[2], O_WRONLY | O_CREAT, FILE_MODE)) == -1) {
		perror("open");
		goto errout;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;		/* IPv4 */
	hints.ai_socktype = SOCK_STREAM;	/* one-to-one style. Read sctp(7) */
	hints.ai_protocol = IPPROTO_SCTP;	/* SCTP */

	if ((err = getaddrinfo(argv[1], SERVER_PORT, &hints, &ailist)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		goto errout;
	}

	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM,
						IPPROTO_SCTP, aip->ai_addr,
						aip->ai_addrlen)) < 0) {
			perror("socket");
			fprintf(stderr, "can't connect to %s\n", argv[1]);
		} else {
			rcv_file(sockfd, fd);
			ret = 0;
			break;
		}
	}

errout:
	if (fd != -1) close(fd);
	if (sockfd != -1) close(sockfd);
	
	return ret;
}
