#include "shell.h"

/**
 * strtow - Splits a string into words using a delimiter as a key
 * @str: The input string
 * @delim: The delimeter string
 * Return: Pointer to a multi-demensional array of strings,
 or NULL on failure
 */

char **strtow(char *str, char *delim)
{
	int a, b, k, m, wordcount = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!delim)
		delim = " ";

	for (a = 0; str[a] != '\0'; a++)
	{
		if (!is_delimiter(str[a], delim) && (is_delimiter(str[a + 1], delim) || !str[a + 1]))
			wordcount++;
	}

	if (wordcount == 0)
		return (NULL);

	s = malloc((1 + wordcount) * sizeof(char *));
	if (!s)
		return (NULL);

	for (a = 0, b = 0; b < wordcount; b++)
	{
		while (is_delimiter(str[a], delim))
			a++;

		k = 0;
		while (!is_delimiter(str[a + k], delim) && str[a + k])
			k++;

		s[b] = malloc((k + 1) * sizeof(char));
		if (!s[b])
		{
			for (k = 0; k < b; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[b][m] = str[a++];

		s[b][m] = '\0';
	}

	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char delim)
{
	int a, b, k, m, wordcount = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (a = 0; str[a] != '\0'; a++)
	{
		if ((str[a] != delim && str[a + 1] == delim) ||
			(str[a] != delim && !str[a + 1]) || str[a + 1] == delim)
			wordcount++;
	}

	if (wordcount == 0)
		return (NULL);

	s = malloc((1 + wordcount) * sizeof(char *));
	if (!s)
		return (NULL);

	for (a = 0, b = 0; b < wordcount; b++)
	{
		while (str[a] == delim && str[a] != '\0')
			a++;

		k = 0;
		while (str[a + k] != delim && str[a + k] && str[a + k] != delim)
			k++;

		s[b] = malloc((k + 1) * sizeof(char));
		if (!s[b])
		{
			for (k = 0; k < b; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[b][m] = str[a++];

		s[b][m] = '\0';
	}

	s[b] = NULL;
	return (s);
}