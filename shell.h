#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define MAX_WORD_COUNT 100
#define NEG_ONE -1
#define REG_FLAG 0
#define OR_FLAG 1
#define AND_FLAG 2
#define CHAIN_FLAG 3
#define BAS_CHANGE_LOWER 1
#define BAS_CHANGE_UNSIG 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE_NAME ".ss_history"
#define HIST_SIZE_MAX 4096
#define SET_INFO							\
	{										\
		NULL, NULL, NULL, 0, 0, 0, 0,		\
		NULL, NULL, NULL, NULL, NULL,		\
		0, 0, NULL, 0, 0, 0					\
	}

extern char **environ;

/**
 * struct ListNode - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct ListNode
{
	int num;
	char *str;
	struct ListNode *next;
} list_s;

/**
 * struct InfoNode - contains simulated arguments for a function pointer,
 *					 allowing for a consistent function prototype
 * @arg: a string generated from getline that holds arguments
 * @argv: an array of strings generated from @arg
 * @path: the path string for the current command
 * @argc: the number of arguments
 * @lines: the number of errors encountered
 * @error_code: the exit() error code
 * @lc_flag: a flag indicating whether this line of input should be counted
 * @prog_name: the name of the program's file
 * @env: a linked list representing a local copy of the environment variables
 * @environ: a custom-modified copy of the environ from the linked list env
 * @history: the node for the command history
 * @alias: the node for the command alias
 * @env_changed: a flag that indicates whether environ has been changed
 * @status: the return status of the most recent executed command
 * @sep_buff: the address of the pointer to sep_buff, used for chaining
 * @sep_buff_kind: the type of command buffer (CMD_type ||, &&, ;)
 * @fd_read: the file descriptor used for reading line input
 * @hist_lines: the number of lines in the history
 */

typedef struct InfoNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prog_name;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;

	char **sep_buff;
	int sep_buff_kind;
	int fd_read;
	int hist_lines;
} info_s;

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_s *);
} builtin_commands;

int shell_main(info_s *info, char **av);
int write_char(char c, int fd);
int write_chars(char *str, int fd);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int putchar_err(char);
int _putchar(char);
int _isalpha(int);
int _atoi(char *);
int err_num(char *);
int handle_exit(info_s *);
int handle_cd(info_s *);
int handle_help(info_s *);
int handle_history(info_s *);
int handle_alias(info_s *);
int _getline(info_s *, char **, size_t *);
int _printenv(info_s *);
int check_setenv(info_s *);
int check_unsetenv(info_s *);
int _unsetenv(info_s *, char *);
int _setenv(info_s *, char *, char *);
void puts_err(char *);
void _puts(char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_memset(char *, char, unsigned int);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(info_s *, const char *);
char *starts_with(const char *, const char *);
char *dup_chars(char *, int, int);
char *check_file_in_path(info_s *info, char *pathstr, char *cmd);
char *change_base(long int, int, int);
char *read_hist(info_s *info);
char **get_environ(info_s *);
char **strtow(char *, char *);
char **list_to_vector(list_s *);
void check_command(info_s *);
void create_process(info_s *);
void handle_sigint(int);
void clear_info(info_s *);
void set_info(info_s *, char **);
void free_info(info_s *, int);
void free_vector(char **);
void print_error(info_s *, char *);
void handle_comments(char *);
void free_list(list_s **);
void check_chain(info_s *info, char *buf, size_t *p, size_t i, size_t len);
int handle_builtin(info_s *);
bool is_executable(info_s *, char *);
int loophsh(char **);
int bfree(void **);
int from_terminal(info_s *);
int print_dec(int, int);
int gather_env(info_s *);
int create_history(info_s *info);
int read_history(info_s *info);
int update_history(info_s *info, char *buf, int linecount);
int renumber_history(info_s *info);
int delete_node_at_index(list_s **, unsigned int);
bool is_chain(info_s *, char *, size_t *);
int change_alias(info_s *);
int change_v(info_s *);
int change_string(char **, char *);
list_s *add_node_start(list_s **head, const char *str, int num);
list_s *add_node_end(list_s **head, const char *str, int num);
list_s *node_str_start(list_s *, char *, char);
size_t print_list_str(const list_s *);
size_t _listlen(const list_s *);
size_t print_list(const list_s *);
ssize_t get_input(info_s *);
ssize_t get_node_index(list_s *, list_s *);
char **split_string(char *str, char *separators, size_t *word_count);
int words_count(char *str, char *separators, unsigned int *arr);
void set_zeros(unsigned int *arr, size_t size);
void set_nulls(char *arr, size_t size);
bool is_delimiter(char c, char *delimiters);

#endif /* SHELL_H */
