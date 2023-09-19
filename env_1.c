#include "shell.h"

/**
 * populate_env_list - Populates env linked list
 * @info: Structure
 * Return: 0 (Success)
 */
int populate_env_list(info__t *info)
{
	list__t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
/**
 * _unsetenv - Removes an environment variable.
 * @info: Structure containing relevant information.
 * @var: The environment variable property to remove.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenv(info__t *info, char *var)
{
	list__t *node = info->env;
	size_t idx = 0;
	char *prop;

	if (!node || !var)
		return (0);

	while (node)
	{
		prop = starts_with(node->str, var);
		if (prop && *prop == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), idx);
			idx = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		idx++;
	}
	return (info->env_changed);
}

/**
 * set_info - Populates the info__t structure.
 * @info: Pointer to the info__t struct.
 * @argv: Argument vector.
 */
void set_info(info__t *info, char **argv)
{
	int a = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		replace_alias(info);
		replace_variables(info);
	}
}