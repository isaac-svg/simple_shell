#include "shell.h"

/**
 * _interactive - returns true if shell is _interactive mode
 * @info: struct pointer
 *
 * Return: 1 if _interactive mode, 0 otherwise
 */

int _interactive(info__t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}





/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; str[a] != '\0' && flag != 2; a++)
	{
		if (str[a] == '-')
			sign *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
