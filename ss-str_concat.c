#include "shell.h"

/**
 * str_concat - concatenates two strings to new array
 * @s1: first string
 * @s2: second string
 *
 * Return: Pointer to newly allocated memory containing
 * concatenated string.
 */

char *str_concat(char *s1, char *s2)
{
	int c, u = 0;
	int len1, len2;
	char *joined;

	/*
	 * If string is NULL or empty, length of array should be 1.
	 * We must first check for null before any other check,
	 * else we would get segmetation error if string happens to be null
	 */
	if (s1 == NULL || s1[0] == '\0')
		len1 = 1;
	else
		for (len1 = 0; s1[len1]; len1++) /* Count length of string 1 */
			continue;

	if (s2 == NULL || s2[0] == '\0')
		len2 = 1;
	else
		for (len2 = 0; s2[len2]; len2++) /* Count length of string 2 */
			continue;

	/* Allocate memory for new array, including null terminaror */
	joined = malloc((sizeof(char) * (len1 + len2)) + 1);

	/* If allocation fails */
	if (!joined)
		return (NULL);

	/* Copy characters from first string */
	if (s1 != NULL)
	{
		for (c = 0; s1[c]; c++, u++)
			joined[u] = s1[c];
	}

	/* Copy characters from second string. */
	if (s2 != NULL)
	{
		for (c = 0; s2[c]; c++, u++)
			joined[u] = s2[c];
	}

	return (joined);
}
