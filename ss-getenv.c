#include "shell.h"

char *_getenv(char *key)
{
    extern char **environ;	/* Access to the environment list */
    char **ptr = environ;	/* Set another pointer to env list */
    size_t namelen = _strlen(key);

    while (*ptr)
	{
        if (_strncmp(*ptr, key, namelen) == 0 && (*ptr)[namelen] == '=')
		{
			/* Return the value of the environment variable */
            return (&((*ptr)[namelen + 1]));
        }
        ptr++;
    }

    return (NULL); /* If environment variable not found */
}