#include "shell.h"



/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	char *ret;
	int len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int b = 0;

	if (!str)
		return;
	while (str[b] != '\0')
	{
		_putchar(str[b]);
		b++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || a >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[a++] = c;
	return (1);
}

/**
 * _strlen - Computes the length of a string
 * @str: The string whose length is to be computed
 *
 * Return: Length of the string as integer
 */
int _strlen(char *str)
{
	int b = 0;

	if (!str)
		return (0);

	while (*str++)
		b++;
	return (b);
}