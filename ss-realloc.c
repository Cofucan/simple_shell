#include "shell.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to previously allocated memory
 * @old_size: size of previously allocated memory
 * @new_size: size of new memory to allocate
 *
 * Return: Pointer to newly allocated memory or NULL.
 */

void *_realloc(void *ptr, unsigned int old_size, size_t new_size)
{
	unsigned int u; /* Counter when copying over elements to new block */
	void *real; /* Pointer to new reallocated address */
	char *cast_ptr;
	char *cast_real;

	/* Return old address if new size is not different from old size */
	if (old_size == new_size)
		return (ptr);

	/* Free up the old block if new size is 0 */
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}

	/* Create the new memory block and return NULL if malloc fails */
	real = malloc(new_size);
	if (real == NULL)
		return (NULL);

	/* If old block contains nothing, return address of new block */
	if (ptr == NULL)
		return (real);

	/*
	 * Cast the old and new memory blocks as char pointers
	 * so we can copy over the elements through array indexing.
	 */
	cast_ptr = ptr;
	cast_real = real;

	/* Copy over each element and leave the extra memory uninitialized */
	for (u = 0; u < old_size; u++)
		cast_real[u] = cast_ptr[u];

	/* We can now free the old address as we have copied over the elements */
	free(ptr);

	return (real);
}
