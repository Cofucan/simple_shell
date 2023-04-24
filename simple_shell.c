#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * main - super simple shell program that runs shell commands
 *
 * When this program is compiled and exeecuted, creates a child process
 * and runs the getline system call and reads the input from stdin.
 * This input should be the path to an executable.
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[], char **env)
{
	char *fullpath = NULL, *buff = NULL, *prompt = "$ ";
	char **args;
	size_t no_of_args, buff_size = 0;
	ssize_t bytes;
	pid_t wpid;
	int wstatus;
	bool from_pipe = false;
	struct stat statbuf;

	while (1 && !from_pipe)
	{
		/* Check if data is piped into program or entered from terminal */
		if (isatty(STDIN_FILENO) == 0)
			from_pipe = true;

		/* Print the prompt sign `$ ` on the terminal */
		write(STDOUT_FILENO, prompt, 2);

		/* Read data from standard input */
		bytes = getline(&buff, &buff_size, stdin);
		if (bytes == -1)
		{
			perror("Error (getline)");
			free(buff);
			exit(EXIT_FAILURE);
		}

		/* Replace the newline character with a null terminator */
		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\0';

		/* Split the arguments string into individual words */
		args = split_string(buff, " ", &no_of_args);

		/* Handle any built-in command that is entered */
		if (handle_builtin(args, no_of_args))
			continue;

		/* Check if executable exists */
		if (!check_file_status(args[0], &statbuf))
		{
			/* Look for executable in the paths */
			fullpath = check_file_in_path(args[0], &statbuf);
			if (!fullpath)
			{
				perror("Error (file status)");
				free_vector(args, no_of_args);
				continue;
			}
			else
			{
				/* Replace the first argument with the full path if exists */
				free(args[0]);
				args[0] = fullpath;
			}
		}

		/* Create a child process and use it to execute the command */
		wpid = fork();
		if (wpid == -1) /* If fork fails */
		{
			perror("Error (fork)");
			free_vector(args, no_of_args);
			exit(EXIT_FAILURE);
		}
		if (wpid == 0) /* Child process */
			execute(args, no_of_args, env);

		/* Parent process should wait for the child process to finish */
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("Error (wait)");
			free_vector(args, no_of_args);
			exit(EXIT_FAILURE);
		}

		/* Free the args vector after the child process ends */
		free_vector(args, no_of_args);
	}

	free(buff);
	return (0);
}

bool handle_builtin(char **args, size_t no_of_args)
{
	/* If the exit command is entered */
	if (_strncmp(args[0], "exit", 4) == 0)
		handle_exit(args, no_of_args);

	/* If the env command is entered */
	else if ((_strncmp(args[0], "env", 3) == 0) || 
		(_strncmp(args[0], "printenv", 8 == 0)))
	{
		handle_env(args, no_of_args);
		return (true);
	}

	return (false);
}

int execute(char **arguments, int no_of_args, char **envp)
{
	execve(arguments[0], arguments, envp);

	/* If execve failed */
	free_vector(arguments, no_of_args);
	perror("Error (execve)"); 
	exit(EXIT_FAILURE);
}

void handle_error(pid_t pid)
{
	if (pid == -1)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
}
