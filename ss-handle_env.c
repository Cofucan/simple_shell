#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
 * handle_env - handles the built-in commands relating to env
 * @env_args: Arguments for the env command.
 * @no_of_args: Number of arguments passed.
 *
 * Return: Nothing
 */

void handle_env(char **env_args, size_t no_of_args)
{
	int set;

	if (!env_args[1])
	{
		if ((_strncmp(env_args[0], "env", 3) == 0)
		|| (_strncmp(env_args[0], "printenv", 8) == 0))
			_printenv();
		else
			write(STDERR_FILENO, "error: not enough arguments\n", 28);
	}
	else if (_strncmp(env_args[0], "setenv", 6) == 0)
	{
		if (no_of_args == 3)
		{
			set = _setenv(env_args[1], env_args[2], 2);
			if (set == -1)
				write(STDERR_FILENO, "error: failed to set variable\n", 30);
		}
		else
			write(STDERR_FILENO, "error: should be 3 arguments\n", 29);
	}

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
