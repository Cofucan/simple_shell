#include "shell.h"

/**
 * _strncmp - This program compares the first n characters
 *			  of two strings.
 *
 * @s1: First string to be compared.
 * @s2: Second string to be compated.
 * @n: Number of characters to compare.
 *
 * Return: negative, positive or zero integer.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	int u, diff;

	for (u = 0; u < n; u++)
	{
		diff = s1[u] - s2[u];
		if (diff > 0 || diff < 0)
			return (diff);
	}

	return (0);
}
