#include "shell.h"
#include <stdarg.h>

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

/**
 * strs_concat - concatenates two or more strings to new array
 * @args_no: Number of strings to be joined.
 * @s1: First string
 * @s2: Second string
 *
 * Return: Pointer to newly allocated memory containing concatenated string.
 */

char *strs_concat(int args_no, const char *s1, const char *s2, ...)
{
	int c, d, u = 0;
	int len = 0;
	char *str, *joined;
	va_list args_main, args_copy;

	/*
	 * If string is NULL or empty, length of array should be 1.
	 * We must first check for null before any other check,
	 * else we would get segmetation error if string happens to be null
	 */

	if (!s1 || !s1[0])
		len = 1;
	else
		len += _strlen(s1); /* Add length of first string */

	if (!s2 || !s2[0])
		len++;
	else
		len += _strlen(s2); /* Add length of second string */

	/* Get length of each extra argument */
	if (args_no > 2)
	{
		va_start(args_main, s2);		/* Store variable arguments */
		va_copy(args_copy, args_main);	/* Make a copy of arguments */

		/* Go over the arguments the first time */
		for (c = 0; c < (args_no - 2); c++)
		{
			str = va_arg(args_main, char *);
			len += (!str || !str[0]) ? 1 : _strlen(str);
		}

		va_end(args_main);				/* End the first arguments' counter */
	}

	/* Allocate memory for new array, including null terminaror */
	joined = malloc((sizeof(char) * len) + 1);

	/* If allocation fails */
	if (!joined)
		return (NULL);

	/* Copy characters from first string */
	if (s1)
		for (c = 0; s1[c]; c++, u++)
			joined[u] = s1[c];

	/* Copy characters from second string. */
	if (s2)
		for (c = 0; s2[c]; c++, u++)
			joined[u] = s2[c];

	/* Copy charcters from each of the extra arguments */
	if (args_no > 2)
	{
		va_start(args_main, s2);		/* Reset the arguments list counter */

		/* Go over the arguments the second time */
		for (d = 0; d < (args_no - 2); d++)
		{
			str = va_arg(args_copy, char *);
			for (c = 0; str[c]; c++, u++)
				joined[u] = str[c];
		}

		/* Clean up argument lists */
		va_end(args_main);
		va_end(args_copy);
	}

	return (joined);
}
