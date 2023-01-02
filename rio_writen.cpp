#include <iostream>
#include <unistd.h>
#include <fcntl.h>

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nwritten;
	char *bufp = reinterpret_cast<char *>(usrbuf);

	while (nleft > 0)
	{
		nwritten = write(fd, bufp, nleft);
		if (nwritten <= 0)
		{
			if(errno == EINTR) /* Interrupted by sig handler return */
				nwritten = 0; /* and call write() again() */
			else
				return -1; /* errno set by write() */
		}
		nleft -= nwritten;
		bufp += nwritten;
	}
	return n;
}