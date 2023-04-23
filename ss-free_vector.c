#include "shell.h"

void free_vector(char **vec, int len)
{
	int x;

	for (x = 0; x < len; x++)
		free(vec[x]);

	free(vec);
}
