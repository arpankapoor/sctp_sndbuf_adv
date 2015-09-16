#include "common.h"
#define QLEN 10

static int
initserver(int type, int protocol, const struct sockaddr *addr,
		socklen_t alen, int qlen)
{
	int fd, err;
	int reuse = -1;

	if ((fd = socket(addr->sa_family, type, protocol)) < 0)
		return -1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
		goto errout;
	if (bind(fd, addr, alen) < 0)
		goto errout;
	if (type == SOCK_STREAM || type == SOCK_SEQPACKET)
		if (listen(fd, qlen) < 0)
			goto errout;

	return fd;

errout:
	err = errno;
	close(fd);
	errno = err;
	return -1;
}

static void
send_file(int sockfd, int fd)
{
	ssize_t read;
	char buf[BUFLEN];

	while ((read = readn(fd, buf, BUFLEN)) > 0)
		if (writen(sockfd, buf, read) < 0)
			perror("write");
}

int
main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addrinfo hints;
	int sockfd = -1,
	    clfd = -1,
	    fd = -1,
	    ret = -1,
	    err;

	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE_TO_SEND\n", argv[0]);
		goto errout;
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror("open");
		goto errout;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;		/* IPv4 */
	hints.ai_socktype = SOCK_STREAM;	/* one-to-one style. Read sctp(7) */
	hints.ai_protocol = IPPROTO_SCTP;	/* SCTP */
	hints.ai_flags = AI_PASSIVE;		/* use my IP */

	if ((err = getaddrinfo(NULL, SERVER_PORT, &hints, &ailist)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		goto errout;
	}

	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, IPPROTO_SCTP,
						aip->ai_addr, aip->ai_addrlen,
						QLEN)) >= 0) {
			printf("waiting for new connection\n");
			if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
				perror("accept");
				goto errout;
			}
			close(sockfd);
			printf("sending file...\n");
			send_file(clfd, fd);
			ret = 0;
			break;
		}
	}

errout:
	if (fd != -1) close(fd);
	if (sockfd != -1) close(sockfd);
	if (clfd != -1) close(clfd);

	return ret;
}
