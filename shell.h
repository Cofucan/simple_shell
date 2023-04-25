#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <math.h>
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

#define MAX_WORD_COUNT 100
#define BUFFER_SIZE 1024

extern char **environ;

int execute(char **arguments, int no_of_args, char **envp);
int words_count(char *str, char *delim, unsigned int *arr);
void handle_error(pid_t pid);
bool handle_builtin(char **args, size_t no_of_args);
void handle_exit(char **exit_args, size_t no_of_args);
void handle_env(char **env_args, size_t no_of_args);
void free_vector(char **vec, int len);
void set_zeros(unsigned int *arr, size_t size);
bool check_file_status(char *pathname, struct stat *statbuf);
bool is_delimiter(char c, char *delimiters);
char *str_concat(char *s1, char *s2);
char *strs_concat(int args_no, char *s1, char *s2, ...);
char *check_file_in_path(char *pathname, struct stat *statbuf);
char **split_string(char *str, char *delim, size_t *word_count);
char *_getenv(char *name);
void *_realloc(void *ptr, unsigned int old_size, size_t new_size);
void _printenv(void);
int _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
int _atoi(char *s);
ssize_t _getline(char **restrict lineptr, size_t *restrict n,
						FILE *restrict stream);

#endif /* !DEBUG */
