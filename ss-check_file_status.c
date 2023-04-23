#include "shell.h"

bool check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);

	/* If file is found based on the provided path */
	if (stat_return == 0)
		return (true);

	return (false);
}

bool check_file_in_path(char *pathname, struct stat *statbuf)
{
	size_t no_of_paths;
	char *current_path = _getenv("PATH");
	char **paths = split_string(current_path, ":", &no_of_paths);

	return (true);
}

