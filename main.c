
#include "shell.h"

/**
 * main - Entry point to program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	int fdes = 2;
	info__t info[] = {INFO_INIT};

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdes)
		: "r" (fdes));

	if (argc == 2)
	{
		fdes = open(argv[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_panicputs(argv[0]);
				_panicputs(": 0: Can't open ");
				_panicputs(argv[1]);
				_panicputchar('\n');
				_panicputchar(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdes;
	}
	populate_env_list(info);
	read_history(info);
	shellfunc(info, argv);
	return (EXIT_SUCCESS);
}