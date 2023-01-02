#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	char str[100];
	printf("%zd\n", sizeof(str));
	size_t cnt = read(0, str, sizeof(str));
	printf("%zd\n", cnt);
	return 0;
}