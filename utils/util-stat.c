#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - this program finds all files specified in the commandline
 *
 * It checks for multiple files from the filepaths (separated by space)
 * entered in the commandline.
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	unsigned int x;
	struct stat statbuf;


	if (argc < 2)
	{
		printf("Usage: %s <filepath> ...\n", argv[0]);
		return (1);
	}

	for (x = 1; argv[x]; x++)
	{
		if (stat(argv[x], &statbuf) == 0)
			printf("SUCCESS: File `%s` was found", argv[x]);
		else
			printf("FAILURE: File `%s` was not found", argv[x]);
		printf("\n");
	}

	return (0);
}
