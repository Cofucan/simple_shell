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
#include <errno.h>

#define MAX_WORD_COUNT 100

int execute(char **arguments, int no_of_args, char **envp);
void handle_error(pid_t pid);
bool check_file_status(char *pathname, struct stat *statbuf);
bool check_file_in_path(char *pathname, struct stat *statbuf);
char **split_string(char *str, char *delim, size_t *word_count);
bool is_delimiter(char c, char *delimiters);
int words_count(char *str, char *delim, unsigned int *arr);
void free_vector(char **vec, int len);
void set_zeros(unsigned int *arr, size_t size);
int _strncmp(char *s1, char *s2, size_t n);
char *str_concat(char *s1, char *s2);
char *_getenv(char *name);
int _strlen(char *s);

#endif /* !DEBUG */
