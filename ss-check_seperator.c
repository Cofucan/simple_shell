#include "shell.h"

/**
 * handle_exit - handles the `exit` built-in command
 * @exit_args: Arrguments for the exit command.
 * @no_of_args: Number of arguments passed.
 *
 * Return: Nothing
 */

char *check_separator(char *str, char **str_ptr)
{
	char *sep1 = ";";
	char *sep2 = "&&";
	char *sep3 = "||";
	int x, start_idx, command_size;

	static unsigned int sep_found;
	static char current_command[BUFFER_SIZE];
	static int idx;

	if (!str[idx])
	{
		idx = 0;
		*str_ptr = NULL;
		return (NULL);
	}

	start_idx = idx;

	for (x = 0; current_command[x]; x++)
		current_command[x] = '\0';

	for (; str[idx]; idx++, (*str_ptr)++)
		if (_strncmp(*str_ptr, " ; ", 3) == 0)
		{
			sep_found = 1;
			command_size = idx - start_idx;
			for (x = 0; x < (command_size); x++, start_idx++)
				current_command[x] = str[start_idx];
			current_command[x] = '\0';
			idx += 3;
			(*str_ptr)+=3;
			break;
		}

	if (!str[idx])
	{
		command_size = idx - start_idx;
		for (x = 0; x < (command_size); x++, start_idx++)
			current_command[x] = str[start_idx];
		current_command[x] = '\0';
		*str_ptr = NULL;
		sep_found = 0;
	}

	return (current_command);
}
