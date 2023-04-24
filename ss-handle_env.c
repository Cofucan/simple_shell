#include "shell.h"
#include <stdio.h>

/**
 * handle_env - handles the `env` built-in command
 * @env_args: Arguments for the env command
 * @no_of_args: Number of arguments passed.
 *
 * Return: Nothing
 */

void handle_env(char **env_args, size_t no_of_args)
{
	if (!env_args[1])
		_printenv();

	free_vector(env_args, no_of_args);
}

/**
 * _printenv - prints the environment variables of the current system
 *
 * Return: Nothing
 */

void _printenv(void)
{
	int var;

	for (var = 0; environ[var]; var++)
		printf("%s\n", environ[var]);
}
