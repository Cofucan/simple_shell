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
char *strs_concat(int args_no, const char *s1, const char *s2, ...);
void *_realloc(void *ptr, unsigned int old_size, size_t new_size);
char **split_string(char *str, char *delim, size_t *word_count);
int _setenv(const char *name, const char *value, int overwrite);
char *check_file_in_path(char *pathname, struct stat *statbuf);
bool check_file_status(char *pathname, struct stat *statbuf);
int words_count(char *str, char *delim, unsigned int *arr);
int _strncmp(const char *s1, const char *s2, size_t n);
void handle_exit(char **exit_args, size_t no_of_args);
char *_memcpy(char *dest, char *src, unsigned int n);
bool handle_builtin(char **args, size_t no_of_args);
void handle_env(char **env_args, size_t no_of_args);
void handle_cd(char **cd_args, size_t no_of_args);
void set_zeros(unsigned int *arr, size_t size);
bool is_delimiter(char c, char *delimiters);
void free_vector(char **vec, int len);
char *str_concat(char *s1, char *s2);
void update_pwd(char *new_pwd);
char *check_separator(char *str, char **str_ptr);
void handle_error(pid_t pid);
int _strlen(const char *s);
char *_getenv(char *name);
void _printenv(void);
int _atoi(char *s);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif /* !DEBUG */
