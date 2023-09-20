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

	path = _getenv("PATH");
	if (path)
	{
		if (stat(command, &buffer) == 0)
			return (command);
		path_copy = _strdup(path);
		command_length = _strlen(command);
		path_token = _strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = _strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			_strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = _strtok(NULL, ":"); }
		}
		return (NULL); }
	return (NULL); }

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

/**
 * *_memcpy - f
 * @dest: dest
 * @src: mem
 * @n: num
 * Return: pointer
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];
	return (dest);
}

/**
 * *_strcpy - f
 * @dest: char
 * @src: char
 * Return: Pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * inttostring - f
 * @num: int
 * Return: int
*/
char *inttostring(int num)
{
	int maxDigits = 12;
	int i;
	char *str;

	str = (char *)malloc(maxDigits * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str); }
	else if (num < 0)
	{
		str[0] = '-';
		num = -num; }
	i = maxDigits - 1;
	str[i] = '\0';
	while (num > 0 && i > 0)
	{
		i--;
		str[i] = '0' + (num % 10);
		num /= 10; }
	return (&str[i]); }
