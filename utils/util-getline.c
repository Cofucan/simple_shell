#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t _getline(char **restrict lineptr, size_t *restrict n,
                       FILE *restrict stream);
ssize_t __getline(char **restrict lineptr, size_t *restrict n,
                       FILE *restrict stream);

int main()
{
	char *buff = NULL;
	ssize_t bytes;
	size_t buff_size = 0;

	printf("$ ");
	bytes = getline(&buff, &buff_size, stdin);
	if (bytes == -1)
	{
		perror("A problem occured!");
		return (-1);
	}

	printf("%s\n", buff);
	free(buff);

	return (0);
}

ssize_t __getline(char **restrict lineptr, size_t *restrict n,
                       FILE *restrict stream)
{
	long byteSize;
	size_t buffSize = 0;

	/* Get the size of the stream in bytes */
	if (fseek(stream, 0L, SEEK_END) == 0)
	{
		byteSize = ftell(stream);
		if (byteSize == -1)
			return (-1);
	}

	/* Set the stream pointer back to the beginning of the stream */
	rewind(stream);

	/* Size of buffer to be allocated, add 1 byte for the null terminator */
	buffSize = (size_t)byteSize + 1;

	/**
	 * Allocate space to store contents of stream.
	 * By using realloc, we can allocate or reallocate automatically
	 * depending on if *lineptr was NULL or is less than the space required
	 */
	if (*n < byteSize)
		*lineptr = (char *)realloc(*lineptr, sizeof(char) * buffSize);

	/* If allocation fails */
	if (*lineptr == NULL)
		return (-1);

	/* Read contents of stream to buffer, if failure, free the buffer */
	if (fgets(*lineptr, buffSize, stream) == NULL)
	{
		free(*lineptr);
		return (-1);
	}

	*n = buffSize;

	return ((ssize_t)*n);
}

ssize_t _getline(char **restrict lineptr, size_t *restrict n,
                       FILE *restrict stream)
{
	long byteSize = 0;
	size_t buffSize = 0;
	char *buffer = NULL;
	char *temp = NULL;

	while (fgets(buffer, *n, stream))
	{
		size_t len = strlen(buffer);
		if (buffer[len - 1] == '\n')
		{
			byteSize += len;
			break;
		}

		byteSize += len;
		temp = realloc(buffer, byteSize);
		if (temp == NULL)
		{
			free(buffer);
			return -1;
		}
		buffer = temp;
	}

	if (ferror(stream) || (!feof(stream) && buffer[0] == '\0'))
	{
		free(buffer);
		return -1;
	}

	*n = byteSize + 1;
	temp = realloc(buffer, *n);
	if (temp == NULL)
	{
		free(buffer);
		return -1;
	}
	buffer = temp;

	rewind(stream);

	size_t i = 0;
	while (fgets(buffer + i, *n - i, stream))
	{
		size_t len = strlen(buffer + i);
		if (buffer[i + len - 1] == '\n')
			break;

		i += len;
		temp = realloc(buffer, *n + i);
		if (temp == NULL)
		{
			free(buffer);
			return -1;
		}
		buffer = temp;
		byteSize += len;
	}

	*lineptr = buffer;

	return byteSize;
}

