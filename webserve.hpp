#include <iostream>
#include <unistd.h>
#include <fcntl.h>

struct rio_t
{
	int rio_fd;
	int rio_cnt;
	char *rio_bufptr;
	char rio_buf[10000];
};

ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
void rio_readinitb(rio_t *rp, int fd);