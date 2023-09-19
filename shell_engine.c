#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter
 * @argv: the argument vector
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info__t *info, char **av)
{
	int b_res = 0;
	ssize_t i_res = 0;

	while (i_res != -1 && b_res != -2)
	{
		clear_info(info);
		if (_interactive(info))
			_puts("$ ");
		_panicputchar(FLUSH_BUFFER);
		i_res = get_input(info);
		if (i_res != -1)
		{
			set_info(info, av);
			b_res = find_builtin(info);
			if (b_res == -1)
				find_cmd(info);
		}
		else if (_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!_interactive(info) && info->status)
		exit(info->status);
	if (b_res == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (b_res);
}

/**
 * find_builtin - Search for a built-in command
 * @inform: Pointer to the info__t structure
 *
 * Return:
 * -1 if the built-in command is not found,
 * 0 if the built-in command is executed successfully,
 * 1 if the built-in command is found but not successful,
 * -2 if the built-in command signals an exit()
 */

int find_builtin(info__t *inform)
{
	int a, ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(inform->argv[0], builtintbl[a].type) == 0)
		{
			inform->line_count++;
			ret = builtintbl[a].func(inform);
			break;
		}
	return (ret);
}

/**
 * find_cmd - finds a command in PATH string
 * @inform: the parameter & return inform struct
 *
 * Return: void
 */
void find_cmd(info__t *inform)
{
	char *path = NULL;
	int a, b;

	inform->path = inform->argv[0];
	if (inform->linecount_flag == 1)
	{
		inform->line_count++;
		inform->linecount_flag = 0;
	}
	for (a = 0, b = 0; inform->arg[a]; a++)
		if (!is_delim(inform->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(inform, _getenv(inform, "PATH="), inform->argv[0]);
	if (path)
	{
		inform->path = path;
		fork_cmd(inform);
	}
	else
	{
		if ((_interactive(inform) || _getenv(inform, "PATH=")
			|| inform->argv[0][0] == '/') && is_cmd(inform, inform->argv[0]))
			fork_cmd(inform);
		else if (*(inform->arg) != '\n')
		{
			inform->status = 127;
			log_error(inform, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inform: the parameter & return inform struct
 *
 * Return: void
 */
void fork_cmd(info__t *inform)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inform->path, inform->argv, get_environ(inform)) == -1)
		{
			free_info(inform, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inform->status));
		if (WIFEXITED(inform->status))
		{
			inform->status = WEXITSTATUS(inform->status);
			if (inform->status == 126)
				log_error(inform, "Permission denied\n");
		}
	}
}
