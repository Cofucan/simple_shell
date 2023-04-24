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

char *check_file_in_path(char *filename, struct stat *statbuf)
{
	size_t s, no_of_paths;
	char *full_path;
	char *current_path = _getenv("PATH");
	char **paths = split_string(current_path, ":", &no_of_paths);

	/* Iterate over each paths */
	for (s = 0; s < no_of_paths; s++)
	{
		/* Concatenate the path with the executable name */
		full_path = strs_concat(3, paths[s], "/", filename);

		if (check_file_status(full_path, statbuf))
		{
			free_vector(paths, no_of_paths);
			return (full_path);
		}
	}

	/* If executable doesn't exist in any of the paths */
	free_vector(paths, no_of_paths);
	free(full_path);
	return (NULL);
}

