#include "shell.h"

int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_var;
	bool exists = false;
	unsigned int env_index = 0;

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL || value == NULL)
	{
        return -1;  /* Invalid arguments */
    }

    /* Check if the environment variable already exists */
    int len_name = _strlen(name);
    int len_value = _strlen(value);
    char **envp = environ;
    while (*envp != NULL)
	{
        if (_strncmp(*envp, name, len_name) == 0 && (*envp)[len_name] == '=')
		{
            if (!overwrite)
			{
                return (0);  /* Already exists and overwrite is not allowed */
            }
			exists = true;
            break;  /* Found and overwrite is allowed */
        }
		env_index++;
        envp++;
    }

	/* Count the number of variables available */
    int num_environ = 0;
    while (environ[num_environ] != NULL)
        num_environ++;

    /* Allocate memory for the new environment variable vector */
    char **new_environ = (char **) malloc((num_environ + 1 + exists) * sizeof(char *));
    if (new_environ == NULL)
	{
        return (-1);  // Memory allocation error
    }

    /* Copy the old environment variables */
    int i = 0;
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
