#include "shell.h"

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing cmd arguments
 *  Return: Always 0
 */

int _myhelp(info__t *info)
{
	char **argv;

	argv = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argv);
	return (0);
}
/**
 * _myexit - exits or closes the shell
 * @info: Structure containing command line arguments
 *  Return: Exit status
 *         
 */
int _myexit(info__t *info)
{
	int exitstate;

	if (info->argv[1])
	{
		exitstate = _panicatoi(info->argv[1]);
		if (exitstate == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_panicputs(info->argv[1]);
			_panicputchar('\n');
			return (1);
		}
		info->err_num = _panicatoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Clone of cd command
 * @info: Structure containing command line arguments
 *  Return: 0 (Success)
 */
int _mycd(info__t *info)
{
	char *str, *directory, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			chdir_ret =
				chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			chdir_ret = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_panicputs(info->argv[1]), _panicputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}