#include "shell.h"
#include <stddef.h>

/**
 * set_zeros - sets all the bytes of an integer array to 0
 * @arr: Array to be initialized.
 * @size: Size of the array.
 *
 * Return: Nothing
 */

void set_zeros(unsigned int *arr, size_t size)
{
	size_t x;

	for (x = 0; x < size; x++)
		arr[x] = 0;
}
