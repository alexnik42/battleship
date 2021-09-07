#include "b_header.h"

void clear_screen(void)
{
	printf("\e[1;1H\e[2J");
}

void clear_stdin(void)
{
	int rc;

	while ((rc = fgetc(stdin)) != '\n' && rc != EOF)
		;
}
