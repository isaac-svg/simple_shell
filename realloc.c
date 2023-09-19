#include "shell.h"

/**
 *_memset - fills memory with a constant byte
 *@arr: Pointer to the memory block
 *@b: the byte to fill the memory with
 *@num: the amount of bytes to be filled
 *Return: Pointer to the memory area
 */
char *_memset(char *arr, char b, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		arr[i] = b;
	return (arr);
}

/**
 * ffree - deallocates a string of strings
 * @memblock: string of strings
 */
void ffree(char **memblock)
{
	char **a = memblock;

	if (!memblock)
		return;
	while (*memblock)
		free(*memblock++);
	free(a);
}

/**
 * _realloc - Clone of realloc
 * @ptr: pointer to previous memory area
 * @prev_size: byte size of previous block
 * @curr_size: byte size of new block
 *
 * Return: Pointer to the new memory block
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int curr_size)
{
	char *p;

	if (!ptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(ptr), NULL);
	if (curr_size == prev_size)
		return (ptr);

	p = malloc(curr_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < curr_size ? prev_size : curr_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}