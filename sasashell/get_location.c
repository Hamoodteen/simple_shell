#include "shell.h"


char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		/* Duplicate the path string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");

		/* let's see if the command itself is a file_path*/
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			/* allocate memory for storing the command name together with the directory name */
			/* NB: we added 2 for the slash and null character we will introduce in the full command */
			file_path = malloc(command_length + directory_length + 2);
			/* to build the path for the command, let's copy the directory path and concatenate the command to it */
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			/* usr/loact/sbin/ls */
			/* let's test if this file path actually exists and return it if it does, otherwise try the next directory */
			if (stat(file_path, &buffer) == 0)
			{
				/* return value of 0 means success implying that the file_path is valid*/
				free(path_copy);
				return (file_path);
			}
			else{
				/* free up the file_path memory so we can check for another path*/
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);        
		return (NULL);
	}
	return (NULL);
}