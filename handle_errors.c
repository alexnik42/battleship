#include "b_header.h"

void handle_errors(void)
{
	if (errno)
		printf("Error: %s\n", strerror(errno));
	else
		printf("Error: something went wrong\n");
}
