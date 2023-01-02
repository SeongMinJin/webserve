#include <sys/types.h>
#include <sys/socket.h> /* for AF_INET, SOCK_STREAM */
#include <netdb.h> /* for struct addrinfo */
#include <iostream>
#include <cstring> /* for memset */
#include <unistd.h>

int main(int ac, char **av)
{
	int clientfd;
	char *host, *port, buf[1000000];
}