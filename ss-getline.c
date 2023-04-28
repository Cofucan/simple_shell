#include "shell.h"

/**
 * _getline - Reads data from a stream into a buffer.
 * @lineptr: Address of buffer where the data will be stored.
 * @n: Address where the size of allocated space will be stored.
 * @stream: File descriptor form which data will be read.
 *
 * Return: Number of bytes read.
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	/* Declare static variables for the buffer and position in the buffer */
	static char buffer[BUFFER_SIZE];
	static char *buffer_pos = buffer;
	static ssize_t buffer_size;

	/* Declare variables for the tracking the characters read */
	char *newline_pos;
	ssize_t bytes_read = 0;
	size_t line_length = 0;

	if (!lineptr || !n || !stream)
	{
		errno = EINVAL;
		return (-1);
	}
	/* Continue loop until we get a complete line or there is no more input */
	while (1)
	{
		/* Check if we need to read more data into the buffer */
		if (buffer_size <= 0)
		{
			/* Call read() to read data from the input stream into the buffer */
			buffer_size = read(fileno(stream), buffer, BUFFER_SIZE);

			/* Check for errors or end-of-file */
			if (buffer_size < 0)
			{
				perror("err (read)");
				return (-1);
			}
			if (buffer_size == 0)
				break;

			/* Reset the buffer position to the beginning of the buffer */
			buffer_pos = buffer;
		}

		/* Search for a newline character in the buffer */
		newline_pos = buffer_pos;

		/* Shift the pointer until the end of the line or newline is found */
		while (newline_pos < buffer + buffer_size && *newline_pos != '\n')
			newline_pos++;

		/* Calculate the length of the line */
		line_length = newline_pos - buffer_pos;

		/* Update *n to reflect the allocated size */
		*n = line_length + 1;	/* Extra byte is for the null terminator */

		/* Allocate or reallocate the line buffer if necessary */
		if (*lineptr == NULL)
			*lineptr = _realloc(*lineptr, bytes_read, bytes_read + line_length + 1);
		/* If allocation fails */
		if (!(*lineptr))
			return (-1);

		/* Copy the line from the buffer to the lineptr buffer */
		_memcpy(*lineptr + bytes_read, buffer_pos, line_length);

		/* Update the line size to include the length of the new line */
		bytes_read += line_length;

		/* Check if we've reached the end of the buffer */
		if (newline_pos == buffer + buffer_size)
			/**
			 * If we have, reset the buffer size to force a read()
			 * on the next iteration.
			 */
			buffer_size = 0;
		else
		{
			/* Otherwise, update the buffer position to the start of the next line */
			buffer_pos = newline_pos + 1;

			/* Null-terminate the line */
			(*lineptr)[bytes_read] = '\0';
			return (bytes_read);
		}
	}
	/* Return the number of bytes read if there is no more input */
	if (*lineptr)
		(*lineptr)[bytes_read] = '\0';
	return (bytes_read);
}
