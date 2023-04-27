#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int _execute(char *executable);
void handle_error(pid_t pid);

/**
 * main - super simple shell program that runs shell commands
 *
 * When this program is compiled and exeecuted, creates a child process
 * and runs the getline system call and reads the input from stdin.
 * This input should be the path to an executable.
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	char *buff = NULL;
	size_t buff_size = 0;
	ssize_t bytes;
	pid_t pid;
	int wstatus;

	while (1)
	{
		printf("$ ");
		bytes = getline(&buff, &buff_size, stdin);
		if (bytes == -1)
		{
			perror("Error:");
			return (1);
		}

		/* Replace the newline character with a null terminator character */
		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\0';

		/* Create a child process and use it to execute the command */
		pid = fork();
		if (pid == 0)
			_execute(buff);
		else 
			wait(&wstatus);
		/* printf("%s", buff); */
	}

	free(buff);
	return (0);
}

int _execute(char *executable)
{
	char *args[2];
	char *exe = executable;
	char *env[] = {"PROJECT=shell", NULL};

	args[0] = exe;
	args[1] = NULL;

	execve(args[0], args, env);

	return (0);
}

void handle_error(pid_t pid)
{
	if (pid == -1)
	{
		printf("Error:");
		exit(98);
	}
}
