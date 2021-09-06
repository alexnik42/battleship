#include "b_header.h"

void print_error(void)
{
	if (errno)
		printf("Error: %s\n", strerror(errno));
	else
		printf("Error: something went wrong\n");
}
