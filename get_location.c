#include "shell.h"

/**
 * _which - get the full path of the command
 * @command: the command
 * Return: the full path of the command
*/
char *_which(char *command)
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
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		return (NULL);
	}
	return (NULL);
}

/**
 * _fgetc - f
 * @stream: file
 * Return: int
*/
int _fgetc(FILE *stream)
{
	char c;
	int nread;

	nread = read(fileno(stream), &c, 1);

	if (nread == 0)
		return (EOF);
	return (c);
}
