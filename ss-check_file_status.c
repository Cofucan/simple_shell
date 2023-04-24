#include "shell.h"

/**
 * check_file_status - checks if a file exists
 * @pathname: Path to the file.
 * @statbuf: Stores information on the file if it is found.
 *
 * Return: True if it is found, else false.
 */

bool check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);

	/* If file is found based on the provided path */
	if (stat_return == 0)
		return (true);

	return (false);
}

/**
 * check_file_in_path - checks if a file exists PATH
 * @filename: Name of the file to be checked.
 * @statbuf: Stores information on the file if it is found.
 *
 * This function search for a file in PATH. If it is found,
 * it concatenates the absolute path with the file name.
 *
 * Return: The full path of the file or NULL if not found.
 */

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

