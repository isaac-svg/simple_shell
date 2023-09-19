#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FLUSH_BUFFER -1
#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024

#define NORMAL_COMMAND	0
#define OR_BUFFER		1
#define AND_BUFFER		2
#define CHAIN_BUFFER	3

#define UNSIGNED_BUFFER	2
#define LOWERCASE_BUFFER	1

#define GETLINE_BUFFER 0


#define HISTORY_FILE	".my_shell_history"
#define MAXIMUM_HISTORY	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list__t;


/**
 * struct passinfo - Structure containing pseudo-arguments for passing into a function
 *
 * @arg: A string representing arguments generated from getline.
 * @argv: An array of strings derived from 'arg,' containing individual arguments.
 * @path: A string indicating the current command's path or location.
 * @argc: An integer representing the count of arguments.
 * @line_count: An integer representing the count of errors encountered.
 * @err_num: An integer representing the error code for potential exit() calls.
 * @linecount_flag: A flag that is set when counting this line of input.
 * @fname: A string containing the filename of the program.
 * @env: A linked list, serving as a local copy of the 'environ' variable.
 * @environ: A custom-modified copy of 'environ' derived from the linked list 'env.'
 * @history: The history node associated with the program.
 * @alias: The alias node associated with the program.
 * @env_changed: A flag that is set if 'environ' has been modified.
 * @status: An integer representing the return status of the last executed command.
 * @cmd_buf: A pointer to a pointer to 'cmd_buf,' used when chaining commands.
 * @cmd_buf_type: The type of 'cmd_buf' (CMD_type) - e.g., '||,' '&&,' ';'
 * @readfd: The file descriptor from which line input is read.
 * @histcount: An integer representing the count of history line numbers.
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list__t *env;
	list__t *history;
	list__t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info__t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a  command and it's
related function
 *@type: The builtin command
 *@func: The  function associated with the command
 */
typedef struct builtin
{
	char *type;
	int (*func)(info__t *);
} builtin_table;


/* string functions */
char *dup_chars(char *str, int n, int m);
int _strlen(char *str);
char *_strchr(char *, char);
char *starts_with(const char *needle, const char *haystack);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);
char *_strncpy(char *str1, char *str2, int n);
char *_strncat(char *dest, char *src, int n);
char *_strdup(const char *src);
char **strtow(char *str1, char *str2);
char **strtow2(char *str, char c);
int _atoi(char *str);


/* terminal, shell functions */
char *_getenv(info__t *info, const char *);
int _mysetenv(info__t *info);
int is_delimiter(char c, char *str);
int _isalpha(int a);
int _interactive(info__t *info);
int shellengine(char **memblock);
void remove_comments(char *comment);
int _myunsetenv(info__t *info);
ssize_t get_cmd(info__t *info);
int replace_variables(info__t *info);
int replace_string(char **memarea, char *a);
void check_chain(info__t *info, char *, size_t *, size_t, size_t);
int replace_alias(info__t *info);
int is_chain(info__t *info, char *str, size_t *n);
int _myexit(info__t *info);
int _mycd(info__t *info);
char *locate_path(info__t *info, char *str1, char *str2);
int _myenv(info__t *info);
int _getline(info__t *info, char **, size_t *);
void sigintHandler(int n);
int _myhelp(info__t *info);
int _myhistory(info__t *info);
int _myalias(info__t *info);




/* stdin, stdout, stderr functions */
int _putchar(char c);
void _puts(char *str);
void log_error(info__t *info, char *str);
int _panicatoi(char *str);
int print_d(int a, int b);
int _panicputchar(char ec);
void _panicputs(char *estr);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);





/* system helper functions */
void fork_command(info__t *info);
int locate_builtin(info__t *info);
int _setenv(info__t *info, char *str1, char *str2);
void find_command(info__t *info);
int is_command(info__t *info, char *str);
int _unsetenv(info__t *info, char *str);
char **get_environ(info__t *info);
int shellfunc(info__t *info, char **memblock);
int populate_env_list(info__t *info);

/* helper functions */
char *_memset(char *, char c, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int a, unsigned int b);

int bfree(void **memblock);


/* history functions */
char *get_history_file(info__t *inform);
int write_history(info__t *inform);
int read_history(info__t *inform);
int create_history_list(info__t *inform, char *buffer, int linecount);
int renumber_history(info__t *inform);


/* struct, linked list functions */



char *convert_number(long int a, int m, int n);
void clear_info(info__t *info);
void set_info(info__t *info, char **memblock);
void free_info(info__t *info, int a);



list__t *add_node(list__t **memarea, const char *str, int a);
list__t *add_node_end(list__t **memarea, const char *str, int b);
size_t print_list_str(const list__t *fnc);
int delete_node_at_index(list__t **memarea, unsigned int n);
void free_list(list__t **memarea);

char **list_to_strings(list__t *cmdptr);
ssize_t get_node_index(list__t *cmdptr, list__t *);
size_t get_len(const list__t *cmdptr);
size_t print_list(const list__t *cmdptr);
int print_alias(list__t *aliasNode);
list__t *node_starts_with(list__t *cmdptr, char *str, char c);


#endif /* SHELL_H */
