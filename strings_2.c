#include "shell.h"


/**
 * _strncat - Concatenates two strings with a maximum byte limit.
 * @str1: The base string
 * @str2: The string to append
 * @maxBytes: The maximum number of bytes
 *
 * Return: The concatenated string.
 */
char *_strncat(char *str1, char *str2, int maxBytes)
{
	char *res = str1;
	int first_idx, scnd_idx;

	first_idx = 0;
	while (str1[first_idx] != '\0')
		first_idx++;

	scnd_idx = 0;
	while (str2[scnd_idx] != '\0' && scnd_idx < maxBytes)
	{
		str1[first_idx] = str2[scnd_idx];
		first_idx++;
		scnd_idx++;
	}

	if (scnd_idx < maxBytes)
		str1[first_idx] = '\0';

	return (res);
}

/**
 * _strchr - Locates a character in a given string.
 * @text: The string to be searched.
 * @character: The character to look for.
 *
 * Return: A pointer to the found character in the string (text).
 */
char *_strchr(char *text, char character)
{
	do
	{
		if (*text == character)
			return (text);
	} while (*text++ != '\0');

	return (NULL);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}