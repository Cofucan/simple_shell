#include "shell.h"
#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	size_t x;
	int y;

	/* for (x = 0; env[x] != NULL; x++)
		printf("%s\n", env[x]); */

	char *path = _getenv("PATH");
	printf("%s\n", path);

	char **paths = split_string(path, ":", &x);
	for (y = 0; paths[y]; y++)
		printf("%d - %s\n", y, paths[y]);

	free_vector(paths, x);
	return (0);
}
