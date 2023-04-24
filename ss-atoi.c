#include "shell.h"

/**
 * _atoi - Entry point
 * @s: String to be converted.
 *
 * This program converts a string to an integer,
 * similar to the atio() function.
 *
 * Return: Integer
 */

int _atoi(char *s)
{
	int sign = 1;
	int number = 0;

	/* Handle empty string */
	if (*(s) == '\0')
		return (0);

	/* Handle signs */
	while (!(*s >= '0' && *s <= '9'))
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}

	/* Handle numbers*/
	while (*s >= '0' && *s <= '9')
	{
		number = (number * 10) + (*s - '0');
		s++;
	}



	return (sign * number);
}
