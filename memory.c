#include "shell.h"

/**
 * _bfree - frees a pointer and sets a address to NULL
 * @memblock: Pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **memblock)
{
	if (memblock && *memblock)
	{
		free(*memblock);
		*memblock = NULL;
		return (1);
	}
	return (0);
}