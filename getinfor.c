#include "shell.h"
/**
 * clear_info - Initializes the info__t structure.
 * @inform: Pointer to the info__t struct.
 */
void clear_info(info__t *inform)
{
	inform->argv = NULL;
	inform->argc = 0;
	inform->arg = NULL;
	inform->path = NULL;
}

/**
 * _setenv - Initializes a new environment variable or modifies an existing one.
 * @inform: Structure containing relevant information.
 * @var: The string representing the environment variable prop.
 * @value: The string representing the environment variable value.
 *
 * Return: Always returns 0.
 */
int _setenv(info__t *inform, char *var, char *value)
{
	char *env_string = NULL;
	list__t *node;
	char *prop;

	if (!var || !value)
		return (0);

	env_string = malloc(_strlen(var) + _strlen(value) + 2);
	if (!env_string)
		return (1);
	_strcpy(env_string, var);
	_strcat(env_string, "=");
	_strcat(env_string, value);
	node = inform->env;
	while (node)
	{
		prop = starts_with(node->str, var);
		if (prop && *prop == '=')
		{
			free(node->str);
			node->str = env_string;
			inform->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inform->env), env_string, 0);
	free(env_string);
	inform->env_changed = 1;
	return (0);
}

/**
 * free_info - Frees fields of the info__t structure.
 * @inform: Pointer to the info__t struct.
 * @all: True if freeing all fields.
 */
void free_info(info__t *inform, int all)
{
	ffree(inform->argv);
	inform->argv = NULL;
	inform->path = NULL;
	if (all)
	{
		if (!inform->cmd_buf)
			free(inform->arg);
		if (inform->env)
			free_list(&(inform->env));
		if (inform->history)
			free_list(&(inform->history));
		if (inform->alias)
			free_list(&(inform->alias));
		ffree(inform->environ);
		inform->environ = NULL;
		bfree((void **)inform->cmd_buf);
		if (inform->readfd > 2)
			close(inform->readfd);
		_putchar(FLUSH_BUFFER);
	}
}