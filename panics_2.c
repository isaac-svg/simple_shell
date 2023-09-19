#include "shell.h"

/**
 * _panicputs - Prints a string to stderr
 * @text: The string to be printed.
 *
 * Return: void
 */
void _panicputs(char *text)
{
	int idx = 0;

	if (!text)
		return;
	while (text[idx] != '\0')
	{
		_panicputchar(text[idx]);
		idx++;
	}
}

/**
 * convert_number - Clone of itoa
 * @num: number
 * @base: number base 
 * @flags: argument flags
 *
 * Return: string of numbers
 */
char *convert_number(long int num, int base, int flags)
{
	static char *digitArray;
	char sign = 0;
	char *resultPtr;
	unsigned long original_number = num;
	static char buffer[50];

	if (!(flags & UNSIGNED_BUFFER) && num < 0)
	{
		original_number = -num;
		sign = '-';
	}

	digitArray = (flags & LOWERCASE_BUFFER) ? "0123456789abcdef" : "0123456789ABCDEF";
	resultPtr = &buffer[49];
	*resultPtr = '\0';

	do
	{
		*--resultPtr = digitArray[original_number % base];
		original_number /= base;
	} while (original_number != 0);

	if (sign)
		*--resultPtr = sign;

	return resultPtr;
}

/**
 * _putfd - Writes a character  to the specified file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to which the character is written.
 *
 * Return: Returns 1 on success.
 * On error, it returns -1, and the errno is set accordingly.
 */

int _putfd(char c, int fd)
{
	static char buffer[WRITE_BUFFER_SIZE];
	static int a;

	if (c == FLUSH_BUFFER || a >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, a);
		a = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[a++] = c;
	return (1);
}

/**
 * remove_comments - Replaces first occurence of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buffer)
{
	int idx;

	for (idx = 0; buffer[idx] != '\0'; idx++)
	{
		if (buffer[idx] == '#' && (!idx || buffer[idx - 1] == ' '))
		{
			buffer[idx] = '\0';
			break;
		}
	}
}
