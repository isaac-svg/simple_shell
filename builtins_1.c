#include "shell.h"

/**
 * unset_alias - Sets  an alias to a  str
 * @info: Struct containing cmd arguments
 * @str: The str alias
 *
 * Return: 0 (success), 1 otherwise
 */

int unset_alias(info__t *info, char *str)
{
	char *esp, saved_char;
	int result;

	esp = _strchr(str, '=');
	if (!esp)
		return 1;

	saved_char = *esp;
	*esp = 0;

	result = delete_node_at_index(&(info->alias),
								  get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*esp = saved_char;
	return result;
}

/**
 * set_alias - Sets an alias to a string
 * @info: Struct containing cmd arguments
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info__t *info, char *str)
{
	char *esp;

	esp = _strchr(str, '=');
	if (!esp)
		return 1;
	if (!*++esp)
		return unset_alias(info, str);

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * _myalias - Clone of alias
 * @info: A structure that may contain arguments and is utilized to uphold a consistent function prototype.
 * Return: This function consistently returns the value 0.
 */

int _myalias(info__t *info)
{
	list__t *node = NULL;
	char *esp = NULL;
	int idx = 0;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return 0;
	}

	for (idx = 1; info->argv[idx]; idx++)
	{
		esp = _strchr(info->argv[idx], '=');
		if (esp)
			set_alias(info, info->argv[idx]);
		else
			print_alias(node_starts_with(info->alias, info->argv[idx], '='));
	}

	return 0;
}

/**
 * _myhistory - Prints the history
 * @info: Structure containing command line arguments
 *
 *  Return: Always 0
 */

int _myhistory(info__t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * print_alias - Print an alias str.
 * @node: The alias node to be printed.
 *
 * Return: 1 (Success), 0 otherwise
 */

int print_alias(list__t *node)
{
	char *esp = NULL, *aliasString = NULL;

	if (node)
	{
		esp = _strchr(node->str, '=');
		for (aliasString = node->str; aliasString <= esp; aliasString++)
			_putchar(*aliasString);
		_putchar('\'');
		_puts(esp + 1);
		_puts("'\n");
		return 0;
	}
	return 1;
}