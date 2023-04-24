#include "shell.h"
#include <stdlib.h>

void handle_exit(char **exit_args, size_t no_of_args)
{
	int status = EXIT_SUCCESS;

	if (exit_args[1])
		status = _atoi(exit_args[1]);

	free_vector(exit_args, no_of_args);
	exit(status);
}
