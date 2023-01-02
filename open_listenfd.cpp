#include <sys/types.h>
#include <sys/socket.h> /* for AF_INET, SOCK_STREAM */
#include <netdb.h> /* for struct addrinfo */
#include <iostream>
#include <cstring> /* for memset */
#include <unistd.h>

int open_listenfd(char *port)
{
	struct addrinfo hints, *listp, *p;
	int listenfd, optval = 1;

	/* Get a list of potential server addresses */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	hints.ai_flags |= AI_NUMERICSERV;
	getaddrinfo(NULL, port, &hints, &listp);

	/* Wlak the list for one that we can bind to */
	for (p = listp; p; p = p->ai_next)
	{
		listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listenfd < 0)
			continue;
		
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const void *>(&optval), sizeof(int));

		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
			break;
		close(listenfd);
	}

	freeaddrinfo(listp);
	if (!p)
		return -1;


	if (listen(listenfd, 1024) < 0)
	{
		close(listenfd);
		return -1;
	}

	return listenfd;
}
