#include "webserve.hpp"

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
	int n, rc;
	char c, *bufp = reinterpret_cast<char *>(usrbuf);

	for (n = 1; n < maxlen; ++n)
	{
		rc = rio_read(rp, &c, 1);
		if (rc == 1)
		{
			*++bufp = c;
			if (c == '\n')
			{
				++n;
				break;
			}
		}
		else if (rc == 0)
		{
			if (n == 1)
				return 0; /* EOF, no data read */
			else
				break; /* EOF, some data was read */
		}
		else
			return -1;
	}
	*bufp = 0;
	return n - 1;
}