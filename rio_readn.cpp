#include "webserve.hpp"

ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = reinterpret_cast<char *>(usrbuf);

	while (nleft > 0)
	{
		nread = read(fd, bufp, nleft);
		if (nread < 0)
		{
			if (errno == EINTR) /* Interrupted by sig handler return */
				nread = 0; /* and call read() agina */
			else
				nread = -1; /* errno set by read() */
		}
		else if (nread == 0)
			break; /* EOF */
		nleft -= nread;
		bufp += nread;
	}
	return n - nleft;	/* return >= 0 */
}