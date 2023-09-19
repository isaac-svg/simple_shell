#include "shell.h"

/**
 * get_environ - Gets a copy of the environment as a string array.
 * @info: Structure containing relevant information.
 *
 * Return: A pointer to the string array containing the environment.
 */
char **get_environ(info__t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


/**
 * _myenv - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *               a constant function prototype.
 * Return: Always 0
 */
int _myenv(info__t *info)
{
	print_list_str(info->env);
	return 0;
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure
 * @name: environment variable name
 *
 * Return: The env variable value
 */
char *_getenv(info__t *info, const char *name)
{
	char *placeholder;
	list__t *node = info->env;

	while (node)
	{
		placeholder = starts_with(node->str, name);
		if (placeholder && *placeholder)
			return placeholder;
		node = node->next;
	}
	return NULL;
}

/**
 * _mysetenv - Sets a new environment variable,
 *             or modify an existing one if present
 * @info: Structure
 *  Return: 0 (Success)
 */
int _mysetenv(info__t *info)
{
	if (info->argc != 3)
	{
		_panicputs("Incorrect number of arguments\n");
		return 1;
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return 0;
	return 1;
}


/**
 * _myunsetenv - Remove an environment variable if present
 * @info: Structure
 *  Return: 0 (Success)
 */
int _myunsetenv(info__t *info)
{
	int a;

	if (info->argc == 1)
	{
		_panicputs("Too few arguments.\n");
		return 1;
	}
	for (a = 1; a < info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return 0;
}

