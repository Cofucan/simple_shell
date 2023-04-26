#include "shell.h"

/**
 * main - super simple shell program that runs shell commands
 * @argc: The number of arguments passed to the program.
 * @argv: Vector containing arguments passed.
 * @env: Environment variables from the current system.
 *
 * When this program is compiled and exeecuted, creates a child process
 * and runs the getline system call and reads the input from stdin.
 * This input should be the path to an executable.
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[], char **env)
{
	char newline = '\n';
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
		bytes = _getline(&buff, &buff_size, stdin);

		if (bytes == 0) /* Handle end-of-file condition */
		{
			write(STDOUT_FILENO, &newline, 1);
			free(buff);
			exit(EXIT_SUCCESS);
		}
		if (bytes == -1) /* Handle getline error */
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

/**
 * handle_builtin - handles the built-in commands
 * @args: Arguments passed to the shell program.
 * @no_of_args: Number of arguments passed.
 *
 * This function handles the different different builtin
 * commands that may be passed into the terminal.
 *
 * Return: True if a built-in command is detected, else false.
 */

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
	/* If the cd command is entered */
	else if (_strncmp(args[0], "cd", 2) == 0)
	{
		handle_cd(args, no_of_args);
		return (true);
	}

	return (false);
}

/**
 * execute - handles the exeution of other processes
 * @arguments: Arguments passed to the shell program.
 * @no_of_args: Number of arguments passed.
 * @envp: Environment variables from the current system.
 *
 * This function handles execution of an executable file
 * if it is detected in the current directory of in PATH.
 *
 * Return: Nothing if successful or error if it fails.
 */

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
