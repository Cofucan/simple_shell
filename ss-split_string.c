#include "shell.h"

/**
 * split_string - splits a string into words specified by a delimiter(s),
 *				  storing the pointer to each word (null-terminated)
 *				  in an array.
 * @str: String to be split.
 * @separators: One or more delimiters by which to split the string.
 * @word_count: Number of words in the string (separated by the delimiters).
 *
 * Return: Vector of pointers to strings (words).
 *		   Remember to free vector after use.
 */

char **split_string(char *str, char *separators, size_t *word_count)
{
	int v, no_of_words;
	char **words;
	char *str_ptr = str;
	unsigned int c, word_sizes[MAX_WORD_COUNT];

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

#include "shell.h"
/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], d) && (is_delimiter(str[i + 1], d) || !str[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter(str[i], d))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
