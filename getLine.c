#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @inform: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: number of bytes read
 */
ssize_t input_buf(info__t *inform, char **buffer, size_t *len)
{
	ssize_t rd = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)inform->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if GETLINE_BUFFER
		rd = getline(buffer, &len_p, stdin);
#else
		rd = _getline(inform, buffer, &len_p);
#endif
		if (rd > 0)
		{
			if ((*buffer)[rd - 1] == '\n')
			{
				(*buffer)[rd - 1] = '\0';
				rd--;
			}
			inform->linecount_flag = 1;
			remove_comments(*buffer);
			create_history_list(inform, *buffer, inform->histcount++);
				*len = rd;
				inform->cmd_buf = buffer;
		}
	}
	return (rd);
}

/**
 * get_input - gets a line minus the newline
 * @inform: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info__t *inform)
{
	static char *buffer;
	static size_t a, j, len;
	ssize_t rd = 0;
	char **buf_p = &(inform->arg), *p;

	_putchar(FLUSH_BUFFER);
	rd = input_buf(inform, &buffer, &len);
	if (rd == -1)
		return (-1);
	if (len)
	{
		j = a;
		p = buffer + a;

		check_chain(inform, buffer, &j, a, len);
		while (j < len)
		{
			if (is_chain(inform, buffer, &j))
				break;
			j++;
		}

		a = j + 1;
		if (a >= len)
		{
			a = len = 0;
			inform->cmd_buf_type = NORMAL_COMMAND;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buffer;
	return (rd); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @inform: parameter struct
 * @buffer: buffer
 * @a: size
 *
 * Return: rd
 */
ssize_t read_buf(info__t *inform, char *buffer, size_t *a)
{
	ssize_t rd = 0;

	if (*a)
		return (0);
	rd = read(inform->readfd, buffer, READ_BUFFER_SIZE);
	if (rd >= 0)
		*a = rd;
	return (rd);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inform: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info__t *inform, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t a, len;
	size_t k;
	ssize_t rd = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	rd = read_buf(inform, buffer, &len);
	if (rd == -1 || (rd == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + a, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffer + a, k - a);
	else
		_strncpy(new_p, buffer + a, k - a + 1);

	s += k - a;
	a = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
