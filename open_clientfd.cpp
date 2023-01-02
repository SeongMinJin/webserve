#include <sys/types.h>
#include <sys/socket.h> /* for AF_INET, SOCK_STREAM */
#include <netdb.h> /* for struct addrinfo */
#include <iostream>
#include <cstring> /* for memset */
#include <unistd.h>


int open_client(char *hostname, char *port)
{
	int clientfd;
	struct addrinfo hints, *listp, *p;

	/* Get a list of potential server addresses */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM; /* Open a connection */
	hints.ai_flags = AI_NUMERICSERV; /* using a numeric port arg */
	hints.ai_flags |= AI_ADDRCONFIG; /* Recommended for connections */
	getaddrinfo(hostname, port, &hints, &listp);


	/* Walk the list for one that we can successfully connect to */
	for (p = listp; p; p = p->ai_next)
	{
		/* Create a socket descriptor */
		clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (clientfd < 0)
			continue;;
		
		/* Connect to server */
		if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
			break; /* Success */
		close(clientfd); /* Connect failed, try another */
	}

	/* Clean up */
	freeaddrinfo(listp);
	if (!p) /* All connects failed */
		return -1;
	else
		return clientfd; /* The last connect succeeded */
}