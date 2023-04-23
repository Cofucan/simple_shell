#include "shell.h"

/**
 * _strlen - counts length of a sting
 * @s: String to be counted
 *
 * This program counts the length of
 * a string by counting each character
 * until the null character is encountered.
 *
 * Return: Number of characters in the string.
 */

int _strlen(char *s)
{
	int count = 0;

	while (*(s + count) != '\0')
	{
		count++;
	}

	return (count);
}
