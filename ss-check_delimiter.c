#include "shell.h"

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: Character to be checked.
 * @delimiters: String of charaters to be compated.
 *
 * This function compares a character to one or more of delimiters
 * to see if the character matches any of the delimiters.
 *
 * Return: True if it is a delimiter, else false.
 */

bool is_delimiter(char c, char *delimiters)
{
	int s;

	for (s = 0; delimiters[s]; s++)
		if (c == delimiters[s])
			return (true);
	return (false);
}
