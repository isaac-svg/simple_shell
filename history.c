#include "shell.h"

/**
 * get_history_file - obtains the history file
 * @inform: structure containing relevant parameters
 *
 * Returns: dynamically allocated string containing the path to the history file
 */

char *get_history_file(info__t *inform)
{
	char *buf, *dir;

	dir = _getenv(inform, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @inform: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info__t *inform)
{
	ssize_t fd;
	char *filename = get_history_file(inform);
	list__t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inform->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * read_history - retrieves history data from a file
 * @inform: the parameter structure
 *
 * Return: the number of history entries loaded on success, 0 otherwise
 */
int read_history(info__t *inform)
{
	struct stat file_stats;
	char *buffer = NULL, *history_file = get_history_file(inform);
	ssize_t fdes, r_leb, f_size = 0;
	int idx, last = 0, line_count = 0;

	if (!history_file)
		return (0);

	fdes = open(history_file, O_RDONLY);
	free(history_file);
	if (fdes == -1)
		return (0);
	if (!fstat(fdes, &file_stats))
		f_size = file_stats.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	r_leb = read(fdes, buffer, f_size);
	buffer[f_size] = 0;
	if (r_leb <= 0)
		return (free(buffer), 0);
	close(fdes);
	for (idx = 0; idx < f_size; idx++)
		if (buffer[idx] == '\n')
		{
			buffer[idx] = 0;
			build_history_list(inform, buffer + last, line_count++);
			last = idx + 1;
		}
	if (last != idx)
		build_history_list(inform, buffer + last, line_count++);
	free(buffer);
	inform->histcount = line_count;
	while (inform->histcount-- >= MAXIMUM_HISTORY)
		delete_node_at_index(&(inform->history), 0);
	renumber_history(inform);
	return (inform->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @inform: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info__t *info, char *line_buffer, int line_count)
{
	list__t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, line_buffer, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @inform: Structure containing potential arguments. Used to maintain
 *
 * Return: The history count
 */
int renumber_history(info__t *info)
{
	int count = 0;
	list__t *node = info->history;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}
	return (info->histcount = count);
}