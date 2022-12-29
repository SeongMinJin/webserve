#include <sys/types.h>
#include <sys/socket.h> /* for AF_INET, SOCK_STREAM */
#include <netdb.h> /* for struct addrinfo */
#include <iostream>
#include <cstring> /* for memset */


int main(int ac, char **av)
{
	struct addrinfo *p, *listp, hints;
	char buf[1000000];
	int rc, flags;


	if (ac != 2)
	{
		std::cerr << "usage:" << av[0] << " <domain name>\n";
		exit(0);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	rc = getaddrinfo(av[1], NULL, &hints, &listp);
	if (rc != 0)
	{
		std::cerr << gai_strerror(rc) << std::endl;
		exit(1);
	}

	flags = NI_NUMERICHOST;
	for(p = listp; p; p = p->ai_next)
	{
		getnameinfo(p->ai_addr, p->ai_addrlen, buf, 1000000, NULL, 0, flags);
		std::cout << buf << std::endl;
	}

	freeaddrinfo(listp);

	return 0;

}