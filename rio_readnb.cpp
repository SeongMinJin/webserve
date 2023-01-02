#include "webserve.hpp"

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = reinterpret_cast<char *>(usrbuf);

	while (nleft > 0)
	{
		nread = rio_read(rp, bufp, nleft);
		if (nread < 0)
			return -1; /* errno set by read() */
		else if (nread == 0)
			break; /* EOF */
		nleft -= nread;
		bufp += nread;
	}
	return n - nleft; /* return >= 0 */
}