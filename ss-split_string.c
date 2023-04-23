#include "shell.h"

/**
 * split_string - splits a string into words specified by a delimiter(s),
 *				  storing the pointer to each word (null-terminated)
 *				  in an array.
 *
 * Return: Vector of pointers to strings (words).
 *		   Remember to free vector after use.
 */

char **split_string(char *str, char *separators, size_t *word_count)
{
	int c, v;
	char **words;
	char *str_ptr = str;
	bool start = false;
	unsigned int no_of_words;
	unsigned int word_sizes[MAX_WORD_COUNT];

	set_zeros(word_sizes, MAX_WORD_COUNT);
	no_of_words = words_count(str, separators, word_sizes);

	if (no_of_words == 0)
		return (NULL);

	/* Allocate space for the vector */
	words = malloc((sizeof(char *) * no_of_words) + 1);
	if (!words)
		return (NULL);

	/* Allocate space for each word in the vector, then copy the word */
	for (v = 0; v < no_of_words; v++)
	{
		/* Allocate for current word */
		words[v] = malloc((sizeof(char) * word_sizes[v]) + 1);
		if (!words[v])
		{
			for (v--; v >= 0; v--)
				free(words[v]);
			free(words);
			return (NULL);
		}

		/* Copy each character of current word to allocated space */
		for (c = 0; c < word_sizes[v]; c++, str_ptr++)
		{
			while (is_delimiter(*str_ptr, separators))
				str_ptr++;

			words[v][c] = *str_ptr;
		};

		/* Add the null byte at the end of the word */
		words[v][c] = '\0';
	}

	/* Store number of words so it can be used to free vector */
	*word_count = no_of_words;

	/* Vector should be null terminated */
	words[v] = NULL;

	return (words);
}
