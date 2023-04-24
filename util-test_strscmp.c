#include "shell.h"
#include <stdio.h>

/**
 * main - this program finds all files specified in the commandline
 *
 * It checks for multiple files from the filepaths (separated by space)
 * entered in the commandline.
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[], char **env)
{
	char *str1 = "/home/cofucan/Desktop/alx";
	char *str2 = "/folder/";
	char *str3 = "mkdir";

	char *str4 = "/bin";
	char *str5 = "/";
	char *str6 = "ls";
	char *joined;

/* 	joined = strs_concat(3, str1, str2, str3); */
/* 	joined = strs_concat(3, str4, str5, str6); */
	joined = strs_concat(9, "Obi ", "is ", "a ", "boy ", "and ", "ada ", "is ", "a ", "girl.");
	printf("%s\n", joined);

	free(joined);
	return (0);
}


void print_env(void)
{
	extern char **environ;
	int s;

	for (s = 0; environ[s]; s++)
		printf("%s\n", environ[s]);
}
