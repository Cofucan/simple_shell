#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#define MAX_WORD_COUNT 100

int execute(char **arguments, int no_of_args, char **envp);
int words_count(char *str, char *delim, unsigned int *arr);
void handle_error(pid_t pid);
void handle_builtin(char **args, size_t no_of_args);
void handle_exit(char **exit_args, size_t no_of_args);
void free_vector(char **vec, int len);
void set_zeros(unsigned int *arr, size_t size);
bool check_file_status(char *pathname, struct stat *statbuf);
bool is_delimiter(char c, char *delimiters);
char *str_concat(char *s1, char *s2);
char *strs_concat(int args_no, char *s1, char *s2, ...);
char *check_file_in_path(char *pathname, struct stat *statbuf);
char **split_string(char *str, char *delim, size_t *word_count);
char *_getenv(char *name);
int _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
int _atoi(char *s);

#endif /* !DEBUG */
