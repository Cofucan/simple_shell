#include "shell.h"

/**
 * _setenv - Enables adding or modifying an environment variable.
 * @name: Name of the variable to create or modify.
 * @value: Value to be assigned to the variable.
 * @overwrite: 0 signifies to only add new variable if it doesn't exist.
 *			   Positive number signifies to replace the variable if it
 *			   already exists, or add new one if it doesn't exist.
 *
 * Return: 0 on success or -1 on failure.
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	int i, num_environ, len_name;
	char *new_var;
	char **new_environ, **envp;
	unsigned int env_index = 0;
	bool exists = false;

	if (name == NULL || name[0] == '\0'
		|| strchr(name, '=') != NULL
		|| value == NULL)
	{
		return (-1);  /* Invalid arguments */
	}

	/* Check if the environment variable already exists */
	len_name = _strlen(name);
	envp = environ;

	while (*envp != NULL)
	{
		if (_strncmp(*envp, name, len_name) == 0 && (*envp)[len_name] == '=')
		{
			if (!overwrite)
			{
				return (0);  /* Already exists and overwrite is not allowed */
			}
			exists = true;
			break;	/* Found and overwrite is allowed */
		}
		env_index++;
		envp++;
	}

	/* Count the number of variables available */
	num_environ = 0;

	while (environ[num_environ] != NULL)
		num_environ++;

	/* Allocate memory for the new environment variable vector */
	new_environ = (char **) malloc((num_environ + 1 + exists) * sizeof(char *));

	if (new_environ == NULL)
	{
		return (-1);  /* Memory allocation error */
	}

	/* Copy the old environment variables */
	i = 0;

	while (environ[i] != NULL)
	{
		new_environ[i] = environ[i];
		i++;
	}

	/* Add the new environment variable, including equal sign and null term */
	new_var = strs_concat(3, name, "=", value);

	if (!exists)
	{ /* If env variable not exists, add it to the end of the list */
		new_environ[i] = new_var;
		new_environ[i + 1] = NULL;
	}
	else
	{ /* If env variable exists, let the pointer point to the new one */
		new_environ[env_index] = new_var;
		new_environ[i] = NULL;
	}

	/* Set the new environment variables */
	environ = new_environ;

	return (0);  /* Success */
}
