#include "shell.h"

/**
 * shell_main - main control for the shell program
 * @info: pointer to an info_s struct containing shell information
 * @av: array of strings containing arguments to the shell
 *
 * Return: the status of the last executed builtin command
 */
int shell_main(info_s *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_return_value = 0;

	while (read_result != -1 && builtin_return_value != -2)
	{
		clear_info(info);

		/* Display the shell prompt if in interactive mode */
		if (from_terminal(info))
			_puts("$ ");

		putchar_err(NEG_ONE);
		read_result = get_input(info);

		/* Handle input if it was successfully read */
		if (read_result != -1)
		{
			set_info(info, av);
			builtin_return_value = handle_builtin(info);

			/* Check for command execution if not a builtin command */
			if (builtin_return_value == -1)
				check_command(info);
		}

		/* Handle end of input if in from_terminal mode */
		else if (from_terminal(info))
			_putchar('\n');

		free_info(info, 0);
	}

	/* Create and store the history list */
	create_history(info);

	/* Free memory and exit */
	free_info(info, 1);
	if (!from_terminal(info) && info->status)
		exit(info->status);

	/* Handle exit with error */
	if (builtin_return_value == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}

	/* Return the last executed builtin command's status */
	return (builtin_return_value);
}

/**
 * handle_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int handle_builtin(info_s *info)
{
	int i, builtin_return_value = -1;

	builtin_commands builtints[] = {
		{"cd", handle_cd},
		{"env", _printenv},
		{"exit", handle_exit},
		{"help", handle_help},
		{"alias", handle_alias},
		{"setenv", check_setenv},
		{"history", handle_history},
		{"unsetenv", check_unsetenv},
		{NULL, NULL}};

	for (i = 0; builtints[i].type; i++)
		if (_strcmp(info->argv[0], builtints[i].type) == 0)
		{
			info->lines++;
			builtin_return_value = builtints[i].func(info);
			break;
		}
	return (builtin_return_value);
}

/**
 * check_command - searches for a command in PATH or the current directory
 * @info: a pointer to the parameter and return info struct
 *
 * Return: void
 */
void check_command(info_s *info)
{
	char *path = NULL;
	int i, word_count;

	info->path = info->argv[0];
	if (info->lc_flag == 1)
	{
		info->lines++;
		info->lc_flag = 0;
	}

	/* Count the number of non-delimiter words in the argument */
	for (i = 0, word_count = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			word_count++;

	/* If there are no words, exit without doing anything */
	if (!word_count)
		return;

	/* Check if the command is in the PATH variable */
	path = check_file_in_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		create_process(info);
	}
	else
	{
		/* Check if the command is in the current directory */
		if ((from_terminal(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
			create_process(info);
		/* If the command is not found, print an error message */
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * create_process - forks a new process to run the command
 * @info: pointer to the parameter & return info struct
 *
 * This function forks a new process and runs the command specified by the
 * @info->argv array. The new process runs in a separate memory space and
 * shares environment variables with the parent process.
 *
 * Return: void
 */
void create_process(info_s *info)
{
	pid_t cpid;

	/* Fork a new process */
	cpid = fork();
	if (cpid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}

	/* Child process: execute the command */
	if (cpid == 0)
	{
		/* Execute the command */
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			/* Handle execve errors */
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	/* Parent process: wait for child process to finish */
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			/* Set return status to child's exit status */
			info->status = WEXITSTATUS(info->status);

			/* Print error message for permission denied errors */
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
