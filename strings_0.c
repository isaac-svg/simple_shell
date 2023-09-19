#include "shell.h"



/**
 * _strcmp - Performs lexicogarphic comparison of two strings
 * @str1: string one
 * @str2: string two
 *
 * Return: positive if str1 > str2, negative if str1 < str2
 * zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next character of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}


/**
 **_strncpy - Copies a string
 *@dest: The destination string
 *@src: The source string
 *@n: The number of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *initial_dest = dest;
	int src_idx, dest_idx;

	src_idx = 0;
	while (src[src_idx] != '\0' && src_idx < n - 1)
	{
		dest[src_idx] = src[src_idx];
		src_idx++;
	}
	if (src_idx < n)
	{
		dest_idx = src_idx;
		while (dest_idx < n)
		{
			dest[dest_idx] = '\0';
			dest_idx++;
		}
	}
	return (initial_dest);
}

/**
 * _strcpy - makes a copy of a string
 * @dest: the destination buffer
 * @src: the source string
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == NULL)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}