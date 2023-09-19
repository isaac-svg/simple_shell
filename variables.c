#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info__t *inform, char *buffer, size_t *p)
{
	size_t b = *p;

	if (buffer[b] == '|' && buffer[b + 1] == '|')
	{
		buffer[b] = 0;
		b++;
		inform->cmd_buf_type = OR_BUFFER;
	}
	else if (buffer[b] == '&' && buffer[b + 1] == '&')
	{
		buffer[b] = 0;
		b++;
		inform->cmd_buf_type = AND_BUFFER;
	}
	else if (buffer[b] == ';')
	{
		buffer[b] = 0;
		inform->cmd_buf_type = CHAIN_BUFFER;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inform: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info__t *inform, char *buffer, size_t *p, size_t i, size_t len)
{
	size_t b = *p;

	if (inform->cmd_buf_type == AND_BUFFER)
	{
		if (inform->status)
		{
			buffer[i] = 0;
			b = len;
		}
	}
	if (inform->cmd_buf_type == OR_BUFFER)
	{
		if (!inform->status)
		{
			buffer[i] = 0;
			b = len;
		}
	}

	*p = b;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inform: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info__t *inform)
{
	int i;
	list__t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inform->alias, inform->argv[0], '=');
		if (!node)
			return (0);
		free(inform->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inform->argv[0] = p;
	}
	return (1);
}

/**
 * replace_variables - replaces vars in the tokenized string
 * @inform: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info__t *inform)
{
	int i = 0;
	list__t *node;

	for (i = 0; inform->argv[i]; i++)
	{
		if (inform->argv[i][0] != '$' || !inform->argv[i][1])
			continue;

		if (!_strcmp(inform->argv[i], "$?"))
		{
			replace_string(&(inform->argv[i]),
				_strdup(convert_number(inform->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inform->argv[i], "$$"))
		{
			replace_string(&(inform->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inform->env, &inform->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inform->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inform->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
