#include <arpa/inet.h>
#include <stdio.h>


int main()
{
	uint32_t ip;
	int res = inet_pton(AF_INET, "128.2.194.242", &ip);
	ip = htonl(ip);
	if (res)
		printf("%X\n", ip);
	return 0;
}