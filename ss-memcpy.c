#include "shell.h"

/**
 * _memcpy - Entry point
 * @dest: Memory area to be filled.
 * @src: Memory area to copy from.
 * @n: Number of bytes to copy.
 *
 * This program copies a n bytes from specified memory area to destination.
 *
 * Return: Pointer to destination.
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int c;

	for (c = 0; c < n; c++)
	{
		dest[c] = src[c];
	}

	return (dest);
}
