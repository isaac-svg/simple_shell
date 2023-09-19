#include "shell.h"

/**
 * _panicatoi - converts a string to an integer
 * for error purpose
 * @str: the string to be converted
 * Return: 0 (if no string is converted), -1 (error)
 */
int _panicatoi(char *str)
{
	unsigned long int res = 0;
	int idx = 0;

	if (*str == '+')
		str++;

	for (idx = 0; str[idx] != '\0'; idx++)
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			res *= 10;
			res += (str[idx] - '0');

			if (res > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}

	return (int)res;
}

/**
 * print_error - Prints an error message to stderr
 * @info: The parameter and return info struct.
 * @error_str: String containing the specified error type.
 */
void print_error(info__t *info, char *error_str)
{
	_panicputs(info->fname);
	_panicputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_panicputs(": ");
	_panicputs(info->argv[0]);
	_panicputs(": ");
	_panicputs(error_str);
}

/**
 * print_d - Prints a decimal number
 * @input: The input
 * @fd: The file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*outputChar)(char) = _putchar;
	int a, char_count = 0;
	unsigned int abspart, curr_digit;

	if (fd == STDERR_FILENO)
		outputChar = _panicputchar;

	if (input < 0)
	{
		abspart = -input;
		outputChar('-');
		char_count++;
	}
	else
	{
		abspart = input;
	}

	curr_digit = abspart;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (abspart / a)
		{
			outputChar('0' + curr_digit / a);
			char_count++;
		}
		curr_digit %= a;
	}

	outputChar('0' + curr_digit);
	char_count++;

	return char_count;
}

/**
 * _panicputchar - Writes a character to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _panicputchar(char c)
{
	static char buffer[WRITE_BUFFER_SIZE];
	static int a;

	if (c == FLUSH_BUFFER || a >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, a);
		a = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[a++] = c;
	return (1);
}

/**
 * _putsfd - Writes an input string to the specified file descriptor.
 * @text: The string to be written.
 * @fd: The file descriptor
 *
 * Return: The count of characters written.
 */
int _putsfd(char *text, int fd)
{
	int char_count = 0;

	if (!text)
		return (0);
	while (*text)
	{
		char_count += _putfd(*text++, fd);
	}
	return (char_count);
}
