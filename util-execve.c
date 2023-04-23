#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void _ls(char *arg, char **env);
void _echo(char *arg, char **env);
void _mkdir(char *arg, char **env);

int main(int argc, char *argv[])
{
	char *env[] = {"MY_NAME=cofucan", NULL};

	if (argc != 2)
	{
		/* printf("No arguments allowed!\n"); */
		printf("Usage: %s argument\n", argv[0]);
		exit(98);
	}
	
	_mkdir(argv[1], env);
	/* _ls(argv[1], env); */
	/* _echo(argv[1], env); */

	perror("A problem occurred");
	return (0);
}

void _ls(char *arg, char **env)
{
	char *args[4];
	char *exe = "/bin/ls";
	char *dir = "/home/cofucan/Desktop/dev/alx/alx-low_level_programming/";

	args[0] = exe;
	args[1] = arg;
	args[2] = dir;
	args[3] = NULL;

	execve(args[0], args, env);
	perror("Error: ls did not work");
}

void _echo(char *arg, char **env)
{
	char *args[3];
	char *exe = "/bin/echo";

	args[0] = exe;
	args[1] = arg;
	args[2] = NULL;

	execve(args[0], args, env);
	perror("Error: echo did not work");
}

void _mkdir(char *arg, char **env)
{
	char *args[3];

	args[0] = "/bin/mkdir";
	args[1] = arg;
	args[2] = NULL;

	execve(args[0], args, env);
}
