#include "shell.h"

/**
 * get_len - Computes length of linked list
 * @head: pointer to head node
 *
 * Return: size of list
 */
size_t get_len(const list__t *head)
{
	size_t cnt = 0;

	while (head)
	{
		head = head->next;
		cnt++;
	}
	return (cnt);
}

/**
 * list_to_strings - returns a string of strings
 * @head: pointer to first node
 *
 * Return: string of strings
 */
char **list_to_strings(list__t *head)
{
	char **str_array;
	char *str;
	size_t list_size = get_len(head), index, j;
	list__t *node = head;

	if (!head || !list_size)
		return (NULL);
	str_array = malloc(sizeof(char *) * (list_size + 1));
	if (!str_array)
		return (NULL);
	for (index = 0; node; node = node->next, index++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < index; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_array[index] = str;
	}
	str_array[index] = NULL;
	return (str_array);
}

/**
 * print_list - prints all elements of a linked list
 * @head: pointer to head node
 *
 * Return: size of list
 */
size_t print_list(const list__t *head)
{
	size_t cnt = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		cnt++;
	}
	return (cnt);
}

/**
 * node_starts_with - check if a string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list__t *node_starts_with(list__t *node, char *prefix, char c)
{
	char *pos = NULL;

	while (node)
	{
		pos = starts_with(node->str, prefix);
		if (pos && ((c == -1) || (*pos == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list__t *head, list__t *node)
{
	size_t idx = 0;

	while (head)
	{
		if (head == node)
			return (idx);
		head = head->next;
		idx++;
	}
	return (-1);
}