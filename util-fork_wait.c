#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int fork_wait(int argc, char *argv[]);
int fork_test();

/**
 * main - fork example
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	fork_wait(argc, argv);
	return (0);
}

/**
 * fork_test - just practicing fork and wait
 *
 * Return: 0 or -1
 */

int fork_test()
{
	pid_t my_pid;
	pid_t pid;
	int wstatus;

/*	printf("Before fork\n"); */
	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}
/*	printf("After fork\n"); */
	my_pid = getpid();
/*	printf("My pid is %u\n", my_pid); */

	if (pid != 0)
		wait(&wstatus);

	if (pid == 0)
		printf("I am a child and my PID is %u\n", my_pid);
	else
		printf("I am the parent and my PID is %u", my_pid);

	return (0);
}

/**
 * fork_wait - fork example from man pages
 *
 * Return: Always 0 or -1.
 */

int fork_wait(int argc, char *argv[])
{
	pid_t cpid, w;
	int wstatus;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0)
	{	/* Code executed by child */
		printf("Child PID is %jd\n", (intmax_t) getpid());
		if (argc == 1)
			pause();	/* Wait for signals */
		_exit(atoi(argv[1]));

	}
	else
	{	/* Code executed by parent */
		do
		{
			w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(wstatus)) {
				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
			} else if (WIFSIGNALED(wstatus)) {
				printf("killed by signal %d\n", WTERMSIG(wstatus));
			} else if (WIFSTOPPED(wstatus)) {
				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
			} else if (WIFCONTINUED(wstatus)) {
				printf("continued\n");
			}
		}
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		exit(EXIT_SUCCESS);
	}
}

