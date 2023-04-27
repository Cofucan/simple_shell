#include "shell.h"

/**
 * handle_exit - handles the `exit` built-in command
 * @exit_args: Arrguments for the exit command.
 * @no_of_args: Number of arguments passed.
 * @buffer: Original buffer where getline stored the data.
 *
 * Return: Nothing
 */

void handle_exit(char **exit_args, size_t no_of_args, char *buffer)
{
	int status = EXIT_SUCCESS;

	if (exit_args[1])
		status = _atoi(exit_args[1]);

	free(buffer);
	free_vector(exit_args, no_of_args);
	exit(status);
}
