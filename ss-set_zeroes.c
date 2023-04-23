#include "shell.h"

void set_zeros(unsigned int *arr, size_t size)
{
	int x;

	for (x = 0; x < size; x++)
		arr[x] = 0;
}
