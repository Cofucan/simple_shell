#include "shell.h"

/**
 * free_vector - frees memory allocated to a 2D character array
 * @vec: Vector to be freed.
 * @len: Number of strings (pointers) in the vector.
 *
 * Return: Nothing.
 */

void free_vector(char **vec, int len)
{
	int x;

	for (x = 0; x < len; x++)
		free(vec[x]);

	free(vec);
}
