#include "shell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 *
 * Return: Always 0.
 */

int main(void)
{
	int s;
	int no_of_words;
	char **words;
	char *test_strings[] = {
		"Hello, my name is Uche. This is shell program.",
		"Uche ",
		" Hello",
		" delimiter x ",
		"C",
		"simple shell project",
	};
	/* char *strb = "/bin/ls && /bin/echo \"hi me\""; */

	words = split_string(test_strings[5], " ,.", &no_of_words);
	for (s = 0; words[s]; s++)
		printf("%s\n", words[s]);

	free_vector(words, no_of_words);

	return (0);
}
