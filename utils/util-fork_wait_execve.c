#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int _execute(int argc, char *argv[]);
void handle_error(pid_t pid);

/**
 * main - program that makes use of fork, wait and execve
 *
 * This program executes a shell command in 5 different child processes.
 * Each child is created by the same parent process.
 * A child must exit before another child is created.
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	pid_t pid = 0;
	int x, this_pid, wstatus;

	
	for (x = 1; x < 5; x++)
	{
		pid = fork();

		if (pid < 0)
		{
			handle_error(pid);
		}
		else if (pid == 0)
		{
			this_pid = getpid();
			printf("\n################### Created Process %d #####################\n", this_pid);
			_execute(argc, argv);
		}
		else
		{
			wait(&wstatus);
			printf("###################### Ended Process %d #####################\n", pid);
		}
	}

	return (0);
}

int _execute(int argc, char *argv[])
{
	char *args[4];
	char *exe = "/bin/ls";
	char *env[] = {"PROJECT=shell", NULL};

	args[0] = exe;
	args[1] = "-l";
	args[2] = "../";
	args[3] = NULL;

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
