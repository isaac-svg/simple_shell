#include "shell.h"

/**
 * add_node - adds a node to the head of the list
 * @head: Pointer to head node
 * @str: str field of node
 * @num: node index
 *
 * Return: Pointer to the new head
 */
list__t *add_node(list__t **memarea, const char *str, int num)
{
	list__t *newNode;

	if (!memarea)
		return (NULL);
	newNode = malloc(sizeof(list__t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list__t));
	newNode->num = num;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	newNode->next = *memarea;
	*memarea = newNode;
	return (newNode);
}

/**
 * add_node_end - adds a node to the tail of the list
 * @head: Pointer to head node
 * @str: string field of node
 * @num: node index
 *
 * Return: Pointer to the new node
 */
list__t *add_node_end(list__t **list, const char *str, int num)
{
	list__t *newNode, *curr_node;

	if (!list)
		return (NULL);

	curr_node = *list;
	newNode = malloc(sizeof(list__t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list__t));
	newNode->num = num;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (curr_node)
	{
		while (curr_node->next)
			curr_node = curr_node->next;
		curr_node->next = newNode;
	}
	else
		*list = newNode;
	return (newNode);
}

/**
 * print_list_str - prints only the str element of a list__t linked list
 * @head: pointer to the head node
 *
 * Return: size of list
 */
size_t print_list_str(const list__t *head)
{
	size_t a = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: Pointer to first node
 * @index: Index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list__t **head, unsigned int index)
{
	list__t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a linked list
 * @head_ptr: Pointer to head node
 *
 * Return: void
 */
void free_list(list__t **head_ptr)
{
	list__t *curr_node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	curr_node = head;
	while (curr_node)
	{
		next_node = curr_node->next;
		free(curr_node->str);
		free(curr_node);
		curr_node = next_node;
	}
	*head_ptr = NULL;
}