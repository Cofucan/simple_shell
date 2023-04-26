#include "shell.h"
#include <unistd.h>

/**
 * handle_cd - handles the `cd` built-in command
 * @cd_args: Arrguments for the cd command.
 * @no_of_args: Number of arguments passed.
 *
 * Return: Nothing
 */

void handle_cd(char **cd_args, size_t no_of_args)
{
	/* Declare them as static so they will persist in memory */
	static char last_dir[BUFFER_SIZE]; /* Directory before change */
	static char curr_dir[BUFFER_SIZE]; /* Directory after change */

	bool prev = false, home = false;
	char *dir, *home_dir;
	int chd;

	if (no_of_args == 1)
	{ /* If the user enters cd with no arguments, go to home dir */
		home = true;
		home_dir = _getenv("HOME");
	}
	else if (_strncmp(cd_args[1], "-", 1) == 0)
	{ /* If the user enters the `-` sign after cd, go to previous dir */
		prev = true;
		_memcpy(curr_dir, last_dir, BUFFER_SIZE);
	}

	/* Store current directory before changing it. */
	dir = getcwd(last_dir, BUFFER_SIZE);
	if (!dir)
		perror("Error (getcwd)");
	else
	{
		if (prev)
		{
			chd = chdir(curr_dir);
			write(STDIN_FILENO, curr_dir, _strlen(curr_dir));
			write(STDIN_FILENO, "\n", 1);
		}
		else if (home)
			chd = chdir(home_dir);
		else
			chd = chdir(cd_args[1]);
		if (chd == -1)
			perror("Error (chdir)");

		/* Store the current dir after changing it, the update PWD env */
		dir = getcwd(curr_dir, BUFFER_SIZE);

		if (_setenv("PWD", dir, 3) == -1)
			write(STDERR_FILENO, "Error! Failed to update PWD.\n", 29);
	}

	free_vector(cd_args, no_of_args);
}

