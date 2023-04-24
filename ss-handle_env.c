#include "shell.h"
#include <stdio.h>

void handle_env(char **env_args, size_t no_of_args)
{
	if (!env_args[1])
		_printenv();

	free_vector(env_args, no_of_args);
}

void _printenv(void)
{
	extern char **environ;
	int var;

	for (var = 0; environ[var]; var++)
		printf("%s\n", environ[var]);
}
