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
	char *fullpath = NULL, *buff = NULL, *command = NULL;
	char *buff_ptr = NULL;
	char **args;
	size_t no_of_args, buff_size = 0;
	ssize_t bytes;
	pid_t wpid;
	int wstatus;
	bool from_pipe = false;
	struct stat statbuf;

	while ((argc > 0) && !from_pipe)
	{
		if (!command)
		{
			/* Check if data is piped into program or entered from terminal */
			if (isatty(STDIN_FILENO) == 0)
				from_pipe = true;

			/* Print the prompt sign `$ ` on the terminal */
			write(STDOUT_FILENO, "$ ", 2);

			/* Read data from standard input */
			bytes = _getline(&buff, &buff_size, stdin);

			if (bytes == 0) /* Handle end-of-file condition */
			{
				write(STDOUT_FILENO, "\n", 1);
				free(buff);
				exit(EXIT_SUCCESS);
			}
			if (bytes == -1) /* Handle getline error */
			{
				write(STDERR_FILENO, argv[0], _strlen(argv[0]));
				perror(": 1");
				free(buff);
				exit(EXIT_FAILURE);
			}

			/* Replace the newline character with a null terminator */
			if (buff[bytes - 1] == '\n')
				buff[bytes - 1] = '\0';
		}

		if (!buff_ptr)
			buff_ptr = buff;

		/* Handle command separators */
		command = check_separator(buff, &buff_ptr);
		if (!command)
			continue;

		/* Split the arguments string into individual words */
		args = split_string(command, " ", &no_of_args);

		/* Handle any built-in command that is entered */
		if (handle_builtin(args, argv[0], no_of_args, buff))
			continue;

		/* Check if executable exists */
		if (!check_file_status(args[0], &statbuf))
		{
			perror(": 9");
			/* Look for executable in the paths */
			fullpath = check_file_in_path(args[0], &statbuf);
			if (!fullpath)
			{
				write(STDERR_FILENO, argv[0], _strlen(argv[0]));
				perror(": 1");
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
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			perror(": 1");
			free_vector(args, no_of_args);
			exit(EXIT_FAILURE);
		}
		if (wpid == 0) /* Child process */
			execute(args, no_of_args, env);

		/* Parent process should wait for the child process to finish */
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			perror(": 1");
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
 * @buffer: Original buffer where getline stored the data.
 *
 * This function handles the different different builtin
 * commands that may be passed into the terminal.
 *
 * Return: True if a built-in command is detected, else false.
 */

bool handle_builtin(char **args, char *prog, size_t no_of_args, char *buffer)
{
	/* If the exit command is entered */
	if (_strncmp(args[0], "exit", 4) == 0)
		handle_exit(args, no_of_args, buffer);

	/* Handle the env, setenv and unsetenv commands */
	else if ((_strncmp(args[0], "env", 3) == 0)
		|| (_strncmp(args[0], "printenv", 8) == 0)
		|| (_strncmp(args[0], "setenv", 6) == 0)
		|| (_strncmp(args[0], "unsetenv", 8) == 0))
	{
		handle_env(args, no_of_args);
		return (true);
	}
	/* If the cd command is entered */
	else if (_strncmp(args[0], "cd", 2) == 0)
	{
		handle_cd(args, no_of_args, prog);
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

/**
 * handle_error - handles errors
 * @pid: Error number type
 *
 * Return: Nothing
 */

void handle_error(pid_t pid)
{
	if (pid == -1)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
}
