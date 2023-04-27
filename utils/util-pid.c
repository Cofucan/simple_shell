#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t my_pid, my_ppid;
	int fd, pid_max;
	char buff[10];

	my_pid = getpid();
	my_ppid = getppid();

	fd = open("/proc/sys/kernel/pid_max", O_RDONLY);
	if (fd == -1)
		return (-1);

	pid_max = read(fd, buff, sizeof(buff));
	if (pid_max == -1)
		return (-1);

	printf("PID \t-> %u\n", my_pid);
	printf("PPID\t-> %u\n", my_ppid);
	dprintf(STDOUT_FILENO, "PID Max -> %s", buff);

	return (0);
}
